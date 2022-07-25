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

#include "compare.h"

//========================================================================
// ����:void	CMP_Inilize(CMP_InitDefine *CMPx)
// ����: ��ʱ����ʼ������.
// ����: CMPx: �ṹ����,��ο�compare.h��Ķ���.
// ����: �ɹ�����0, �ղ�������1,���󷵻�2.
// �汾: V1.0, 2012-10-22
//========================================================================
void	CMP_Inilize(CMP_InitDefine *CMPx)
{
	CMPCR1 = 0;
	CMPCR2 = CMPx->CMP_OutDelayDuty & 0x3f;										//�ȽϽ���仯��ʱ������, 0~63
	if(CMPx->CMP_EN == ENABLE)				CMPCR1 |= CMPEN;				//����Ƚ���		ENABLE,DISABLE
	if(CMPx->CMP_RiseInterruptEn == ENABLE)	CMPCR1 |= PIE;		//�����������ж�	ENABLE,DISABLE
	if(CMPx->CMP_FallInterruptEn == ENABLE)	CMPCR1 |= NIE;		//�����½����ж�	ENABLE,DISABLE
	if(CMPx->CMP_P_Select  == CMP_P_ADC)	CMPCR1 |= PIS;			//�Ƚ�������������ѡ��, CMP_P_P37: ѡ���ڲ�P3.7��������, CMP_P_ADC: ��ADCIS[2:0]��ѡ���ADC�������������.
	if(CMPx->CMP_N_Select  == CMP_N_P36)	CMPCR1 |= NIS;			//�Ƚ������븺����ѡ��, CMP_N_GAP: ѡ���ڲ�BandGap��ѹBGv��������, CMP_N_P36: ѡ���ⲿP3.6������.
	if(CMPx->CMP_Outpt_En == ENABLE)		CMPCR1 |= CMPOE;			//����ȽϽ�������P3.4/P4.1,   ENABLE,DISABLE
	if(CMPx->CMP_InvCMPO     == ENABLE)		CMPCR2 |= INVCMPO;	//�Ƚ������ȡ��, 	ENABLE,DISABLE
	if(CMPx->CMP_100nsFilter == DISABLE)	CMPCR2 |= DISFLT;		//�ڲ�0.1uF�˲�,  	ENABLE,DISABLE
	P_SW2 = (P_SW2 & ~(0x08)) | CMPx->CMP_P_SW;
	if(CMPx->CMP_Priority > Priority_3)	return;		//����
	CMP_Priority(CMPx->CMP_Priority);		//ָ���ж����ȼ�(�͵���) Priority_0,Priority_1,Priority_2,Priority_3
}

/********************* UART1�жϺ���************************/
void CMP_int (void) interrupt CMP_VECTOR
{
	CMPCR1 &= ~CMPIF;			//����жϱ�־
	P47 = CMPCR1 & 0x01;	//�жϷ�ʽ��ȡ�Ƚ����ȽϽ��
}
