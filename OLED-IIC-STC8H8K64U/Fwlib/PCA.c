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

#include	"PCA.h"

bit		B_Capture0,B_Capture1,B_Capture2;
u8		PCA0_mode,PCA1_mode,PCA2_mode;
u16		CCAP0_tmp,PCA_Timer0;
u16		CCAP1_tmp,PCA_Timer1;
u16		CCAP2_tmp,PCA_Timer2;

/*************	����˵��	**************


******************************************/


//========================================================================
// ����: UpdatePwm(u8 PCA_id, u16 pwm_value)
// ����: ����PWMֵ. 
// ����: PCA_id: PCA���. ȡֵ PCA0,PCA1,PCA2,PCA_Counter
//		 pwm_value: pwmֵ, ���ֵ������͵�ƽ��ʱ��.
// ����: none.
// �汾: V1.0, 2012-11-22
//========================================================================
void	UpdatePwm(u8 PCA_id, u16 pwm_value)
{
	if(PCA_id == PCA0)
	{
		PCA_PWM0 = (PCA_PWM0 & ~0x32) | (u8)((pwm_value & 0x0300) >> 4) | (u8)((pwm_value & 0x0400) >> 9);
		CCAP0H = (u8)pwm_value;
	}
	else if(PCA_id == PCA1)
	{
		PCA_PWM1 = (PCA_PWM1 & ~0x32) | (u8)((pwm_value & 0x0300) >> 4) | (u8)((pwm_value & 0x0400) >> 9);
		CCAP1H = (u8)pwm_value;
	}
	else if(PCA_id == PCA2)
	{
		PCA_PWM2 = (PCA_PWM2 & ~0x32) | (u8)((pwm_value & 0x0300) >> 4) | (u8)((pwm_value & 0x0400) >> 9);
		CCAP2H = (u8)pwm_value;
	}
}

//========================================================================
// ����: void	PCA_Init(PCA_id, PCA_InitTypeDef *PCAx)
// ����: PCA��ʼ������.
// ����: PCA_id: PCA���. ȡֵ PCA0,PCA1,PCA2,PCA_Counter
//		 PCAx: �ṹ����,��ο�PCA.h��Ķ���.
// ����: none.
// �汾: V1.0, 2012-11-22
//========================================================================
void	PCA_Init(u8 PCA_id, PCA_InitTypeDef *PCAx)
{
	if(PCA_id > PCA_Counter)	return;		//id����

	if(PCA_id == PCA_Counter)			//���ù���Counter
	{
		CR = 0;
		CH = 0;
		CL = 0;
		P_SW1 = (P_SW1 & ~(3<<4)) | PCAx->PCA_IoUse;			//�л�IO��
		CMOD  = (CMOD  & ~(7<<1)) | PCAx->PCA_Clock;			//ѡ��ʱ��Դ
		CMOD  = (CMOD  & ~1) | (PCAx->PCA_Interrupt_Mode & 1);	//ECF
		if(PCAx->PCA_Priority > Priority_3)	return;	//����
		PCA_Priority(PCAx->PCA_Priority);	//ָ���ж����ȼ�(�͵���) Priority_0,Priority_1,Priority_2,Priority_3
		if(PCAx->PCA_RUN == ENABLE)	CR = 1;
		return;
	}

	PCAx->PCA_Interrupt_Mode &= (3<<4) + 1;
	if(PCAx->PCA_Mode >= PCA_Mode_SoftTimer)	PCAx->PCA_Interrupt_Mode &= ~(3<<4);

	if(PCA_id == PCA0)
	{
		CCAPM0    = PCAx->PCA_Mode | PCAx->PCA_Interrupt_Mode;	//����ģʽ, �ж�ģʽ
		PCA_PWM0  = (PCA_PWM0 & ~(3<<6)) | PCAx->PCA_PWM_Wide;	//PWM���

		PCA_Timer0 = PCAx->PCA_Value;
		B_Capture0 = 0;
		PCA0_mode = PCAx->PCA_Mode;
		CCAP0_tmp = PCA_Timer0;
		CCAP0L = (u8)CCAP0_tmp;			//��Ӱ��Ĵ���д�벶��Ĵ�������дCCAP0L
		CCAP0H = (u8)(CCAP0_tmp >> 8);	//��дCCAP0H
	}
	if(PCA_id == PCA1)
	{
		CCAPM1    = PCAx->PCA_Mode | PCAx->PCA_Interrupt_Mode;
		PCA_PWM1  = (PCA_PWM1 & ~(3<<6)) | PCAx->PCA_PWM_Wide;

		PCA_Timer1 = PCAx->PCA_Value;
		B_Capture1 = 0;
		PCA1_mode = PCAx->PCA_Mode;
		CCAP1_tmp = PCA_Timer1;
		CCAP1L = (u8)CCAP1_tmp;			//��Ӱ��Ĵ���д�벶��Ĵ�������дCCAP0L
		CCAP1H = (u8)(CCAP1_tmp >> 8);	//��дCCAP0H
	}
	if(PCA_id == PCA2)
	{
		CCAPM2    = PCAx->PCA_Mode | PCAx->PCA_Interrupt_Mode;
		PCA_PWM2  = (PCA_PWM2 & ~(3<<6)) | PCAx->PCA_PWM_Wide;

		PCA_Timer2 = PCAx->PCA_Value;
		B_Capture2 = 0;
		PCA2_mode = PCAx->PCA_Mode;
		CCAP2_tmp = PCA_Timer2;
		CCAP2L = (u8)CCAP2_tmp;			//��Ӱ��Ĵ���д�벶��Ĵ�������дCCAP0L
		CCAP2H = (u8)(CCAP2_tmp >> 8);	//��дCCAP0H
	}
}


//========================================================================
// ����: void	PCA_Handler (void) interrupt PCA_VECTOR
// ����: PCA�жϴ������.
// ����: None
// ����: none.
// �汾: V1.0, 2012-11-22
//========================================================================
void	PCA_Handler (void) interrupt PCA_VECTOR
{
	if(CCF0)		//PCAģ��0�ж�
	{
		CCF0 = 0;		//��PCAģ��0�жϱ�־
		if(PCA0_mode >= PCA_Mode_SoftTimer)		//PCA_Mode_SoftTimer and PCA_Mode_HighPulseOutput
		{
			CCAP0_tmp += PCA_Timer0;
			CCAP0L = (u8)CCAP0_tmp;			//��Ӱ��Ĵ���д�벶��Ĵ�������дCCAP0L
			CCAP0H = (u8)(CCAP0_tmp >> 8);	//��дCCAP0H
		}
		else if(PCA0_mode == PCA_Mode_Capture)
		{
			CCAP0_tmp = CCAP0H;	//��CCAP0H
			CCAP0_tmp = (CCAP0_tmp << 8) + CCAP0L;
			B_Capture0 = 1;
		}
	}

	if(CCF1)	//PCAģ��1�ж�
	{
		CCF1 = 0;		//��PCAģ��1�жϱ�־
		if(PCA1_mode >= PCA_Mode_SoftTimer)		//PCA_Mode_SoftTimer and PCA_Mode_HighPulseOutput
		{
			CCAP1_tmp += PCA_Timer1;
			CCAP1L = (u8)CCAP1_tmp;			//��Ӱ��Ĵ���д�벶��Ĵ�������дCCAP0L
			CCAP1H = (u8)(CCAP1_tmp >> 8);	//��дCCAP0H
		}
		else if(PCA1_mode == PCA_Mode_Capture)
		{
			CCAP1_tmp = CCAP1H;	//��CCAP1H
			CCAP1_tmp = (CCAP1_tmp << 8) + CCAP1L;
			B_Capture1 = 1;
		}
	}

	if(CCF2)	//PCAģ��2�ж�
	{
		CCF2 = 0;		//��PCAģ��1�жϱ�־
		if(PCA2_mode >= PCA_Mode_SoftTimer)		//PCA_Mode_SoftTimer and PCA_Mode_HighPulseOutput
		{
			CCAP2_tmp += PCA_Timer2;
			CCAP2L = (u8)CCAP2_tmp;			//��Ӱ��Ĵ���д�벶��Ĵ�������дCCAP0L
			CCAP2H = (u8)(CCAP2_tmp >> 8);	//��дCCAP0H
		}
		else if(PCA2_mode == PCA_Mode_Capture)
		{
			CCAP2_tmp = CCAP2H;	//��CCAP2H
			CCAP2_tmp = (CCAP2_tmp << 8) + CCAP2L;
			B_Capture2 = 1;
		}
	}

	if(CF)	//PCA����ж�
	{
		CF = 0;			//��PCA����жϱ�־
	}

}