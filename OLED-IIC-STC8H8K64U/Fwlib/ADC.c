/*---------------------------------------------------------------------*/
/* --- STC MCU Limited ------------------------------------------------*/
/* --- STC 1T Series MCU Demo Programme -------------------------------*/
/* --- Mobile: (86)13922805190 ----------------------------------------*/
/* --- Fax: 86-0513-55012956,55012947,55012969 ------------------------*/
/* --- Tel: 86-0513-55012928,55012929,55012966 ------------------------*/
/* --- Web: www.STCMCU.com --------------------------------------------*/
/* --- Web: www.STCMCUDATA.com  ---------------------------------------*/
/* --- QQ:  800003751 -------------------------------------------------*/
/* ���Ҫ�ڳ�����ʹ�ô˴���,���ڳ�����ע��ʹ����STC�����ϼ�����            */
/*---------------------------------------------------------------------*/

#include	"adc.h"


//========================================================================
// ����: void	ADC_Inilize(ADC_InitTypeDef *ADCx)
// ����: ADC��ʼ������.
// ����: ADCx: �ṹ����,��ο�adc.h��Ķ���.
// ����: none.
// �汾: V1.0, 2012-10-22
//========================================================================
void	ADC_Inilize(ADC_InitTypeDef *ADCx)
{
	ADCCFG = (ADCCFG & ~ADC_SPEED_2X16T) | ADCx->ADC_Speed;
	if(ADCx->ADC_Power == ENABLE)	ADC_CONTR |= 0x80;
	else							ADC_CONTR &= 0x7F;
	if(ADCx->ADC_AdjResult == ADC_RIGHT_JUSTIFIED)	ADCCFG |=  (1<<5);	//ADת������Ҷ��롣
	else									ADCCFG &= ~(1<<5);	//ADת���������롣 
	if(ADCx->ADC_Interrupt == ENABLE)	EADC = 1;			//�ж�����		ENABLE,DISABLE
	else								EADC = 0;
	if(ADCx->ADC_Priority > Priority_3)	return;	//����
	ADC_Priority(ADCx->ADC_Priority);	//ָ���ж����ȼ�(�͵���) Priority_0,Priority_1,Priority_2,Priority_3

	if(ADCx->ADC_SMPduty > 31)	return;	//����
	if(ADCx->ADC_CsSetup > 1)	return;	//����
	if(ADCx->ADC_CsHold > 3)	return;	//����
	P_SW2 |= 0x80;
	ADCTIM = (ADCx->ADC_CsSetup << 7) | (ADCx->ADC_CsHold << 5) | ADCx->ADC_SMPduty ;		//���� ADC �ڲ�ʱ��ADC����ʱ�佨�������ֵ
	P_SW2 &= 0x7f;
}


//========================================================================
// ����: void	ADC_PowerControl(u8 pwr)
// ����: ADC��Դ���Ƴ���.
// ����: pwr: ��Դ����,ENABLE��DISABLE.
// ����: none.
// �汾: V1.0, 2012-10-22
//========================================================================
void	ADC_PowerControl(u8 pwr)
{
	if(pwr == ENABLE)	ADC_CONTR |= 0x80;
	else				ADC_CONTR &= 0x7f;
}

//========================================================================
// ����: u16	Get_ADCResult(u8 channel)
// ����: ��ѯ����һ��ADC���.
// ����: channel: ѡ��Ҫת����ADC.
// ����: ADC���.
// �汾: V1.0, 2012-10-22
//========================================================================
u16	Get_ADCResult(u8 channel)	//channel = 0~15
{
	u16	adc;
	u8	i;

	if(channel > ADC_CH15)	return	4096;	//����,����4096,���õĳ����ж�	
	ADC_RES = 0;
	ADC_RESL = 0;

	ADC_CONTR = (ADC_CONTR & 0xf0) | ADC_START | channel; 
	NOP(10);			//��ADC_CONTR������ȴ�����ٷ���

	for(i=0; i<250; i++)		//��ʱ
	{
		if(ADC_CONTR & ADC_FLAG)
		{
			ADC_CONTR &= ~ADC_FLAG;
			if(ADCCFG &  (1<<5))		//ת������Ҷ��롣 
			{
				adc = ((u16)ADC_RES << 8) | ADC_RESL;
			}
			else		//ת���������롣 
			{
				#if ADC_RES_12BIT==1
					adc = (u16)ADC_RES;
					adc = (adc << 4) | ((ADC_RESL >> 4)&0x0f);
				#else
					adc = (u16)ADC_RES;
					adc = (adc << 2) | ((ADC_RESL >> 6)&0x03);
				#endif
			}
			return	adc;
		}
	}
	return	4096;	//����,����4096,���õĳ����ж�
}


//========================================================================
// ����: void ADC_int(void) interrupt ADC_VECTOR
// ����: ADC�жϺ���.
// ����: none.
// ����: none.
// �汾: V1.0, 2012-10-22
//========================================================================
void ADC_int (void) interrupt ADC_VECTOR
{
	ADC_CONTR &= ~ADC_FLAG;
}


