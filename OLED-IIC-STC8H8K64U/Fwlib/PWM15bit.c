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

#include	"PWM15bit.h"

u16 code PWMxCR[48] = {
	0xff14,		/* PWM00CR */
	0xff1c,		/* PWM01CR */
	0xff24,		/* PWM02CR */
	0xff2c,		/* PWM03CR */
	0xff34,		/* PWM04CR */
	0xff3c,		/* PWM05CR */
	0xff44,		/* PWM06CR */
	0xff4c,		/* PWM07CR */
	0xff64,		/* PWM10CR */
	0xff6c,		/* PWM11CR */
	0xff74,		/* PWM12CR */
	0xff7c,		/* PWM13CR */
	0xff84,		/* PWM14CR */
	0xff8c,		/* PWM15CR */
	0xff94,		/* PWM16CR */
	0xff9c,		/* PWM17CR */
	0xffb4,		/* PWM20CR */
	0xffbc,		/* PWM21CR */
	0xffc4,		/* PWM22CR */
	0xffcc,		/* PWM23CR */
	0xffd4,		/* PWM24CR */
	0xffdc,		/* PWM25CR */
	0xffe4,		/* PWM26CR */
	0xffec,		/* PWM27CR */
	0xfc14,		/* PWM30CR */
	0xfc1c,		/* PWM31CR */
	0xfc24,		/* PWM32CR */
	0xfc2c,		/* PWM33CR */
	0xfc34,		/* PWM34CR */
	0xfc3c,		/* PWM35CR */
	0xfc44,		/* PWM36CR */
	0xfc4c,		/* PWM37CR */
	0xfc64,		/* PWM40CR */
	0xfc6c,		/* PWM41CR */
	0xfc74,		/* PWM42CR */
	0xfc7c,		/* PWM43CR */
	0xfc84,		/* PWM44CR */
	0xfc8c,		/* PWM45CR */
	0xfc94,		/* PWM46CR */
	0xfc9c,		/* PWM47CR */
	0xfcb4,		/* PWM50CR */
	0xfcbc,		/* PWM51CR */
	0xfcc4,		/* PWM52CR */
	0xfccc,		/* PWM53CR */
	0xfcd4,		/* PWM54CR */
	0xfcdc,		/* PWM55CR */
	0xfce4,		/* PWM56CR */
	0xfcec,		/* PWM57CR */
};

u16 code PWMxT1[48] = {
	0xff10,		/* PWM00T1 */
	0xff18,		/* PWM01T1 */
	0xff20,		/* PWM02T1 */
	0xff28,		/* PWM03T1 */
	0xff30,		/* PWM04T1 */
	0xff38,		/* PWM05T1 */
	0xff40,		/* PWM06T1 */
	0xff48,		/* PWM07T1 */
	0xff60,		/* PWM10T1 */
	0xff68,		/* PWM11T1 */
	0xff70,		/* PWM12T1 */
	0xff78,		/* PWM13T1 */
	0xff80,		/* PWM14T1 */
	0xff88,		/* PWM15T1 */
	0xff90,		/* PWM16T1 */
	0xff98,		/* PWM17T1 */
	0xffb0,		/* PWM20T1 */
	0xffb8,		/* PWM21T1 */
	0xffc0,		/* PWM22T1 */
	0xffc8,		/* PWM23T1 */
	0xffd0,		/* PWM24T1 */
	0xffd8,		/* PWM25T1 */
	0xffe0,		/* PWM26T1 */
	0xffe8,		/* PWM27T1 */
	0xfc10,		/* PWM30T1 */
	0xfc18,		/* PWM31T1 */
	0xfc20,		/* PWM32T1 */
	0xfc28,		/* PWM33T1 */
	0xfc30,		/* PWM34T1 */
	0xfc38,		/* PWM35T1 */
	0xfc40,		/* PWM36T1 */
	0xfc48,		/* PWM37T1 */
	0xfc60,		/* PWM40T1 */
	0xfc68,		/* PWM41T1 */
	0xfc70,		/* PWM42T1 */
	0xfc78,		/* PWM43T1 */
	0xfc80,		/* PWM44T1 */
	0xfc88,		/* PWM45T1 */
	0xfc90,		/* PWM46T1 */
	0xfc98,		/* PWM47T1 */
	0xfcb0,		/* PWM50T1 */
	0xfcb8,		/* PWM51T1 */
	0xfcc0,		/* PWM52T1 */
	0xfcc8,		/* PWM53T1 */
	0xfcd0,		/* PWM54T1 */
	0xfcd8,		/* PWM55T1 */
	0xfce0,		/* PWM56T1 */
	0xfce8,		/* PWM57T1 */
};

u16 code PWMxT2[48] = {
	0xff12,		/* PWM00T2 */
	0xff1a,		/* PWM01T2 */
	0xff22,		/* PWM02T2 */
	0xff2a,		/* PWM03T2 */
	0xff32,		/* PWM04T2 */
	0xff3a,		/* PWM05T2 */
	0xff42,		/* PWM06T2 */
	0xff4a,		/* PWM07T2 */
	0xff62,		/* PWM10T2 */
	0xff6a,		/* PWM11T2 */
	0xff72,		/* PWM12T2 */
	0xff7a,		/* PWM13T2 */
	0xff82,		/* PWM14T2 */
	0xff8a,		/* PWM15T2 */
	0xff92,		/* PWM16T2 */
	0xff9a,		/* PWM17T2 */
	0xffb2,		/* PWM20T2 */
	0xffba,		/* PWM21T2 */
	0xffc2,		/* PWM22T2 */
	0xffca,		/* PWM23T2 */
	0xffd2,		/* PWM24T2 */
	0xffda,		/* PWM25T2 */
	0xffe2,		/* PWM26T2 */
	0xffea,		/* PWM27T2 */
	0xfc12,		/* PWM30T2 */
	0xfc1a,		/* PWM31T2 */
	0xfc22,		/* PWM32T2 */
	0xfc2a,		/* PWM33T2 */
	0xfc32,		/* PWM34T2 */
	0xfc3a,		/* PWM35T2 */
	0xfc42,		/* PWM36T2 */
	0xfc4a,		/* PWM37T2 */
	0xfc62,		/* PWM40T2 */
	0xfc6a,		/* PWM41T2 */
	0xfc72,		/* PWM42T2 */
	0xfc7a,		/* PWM43T2 */
	0xfc82,		/* PWM44T2 */
	0xfc8a,		/* PWM45T2 */
	0xfc92,		/* PWM46T2 */
	0xfc9a,		/* PWM47T2 */
	0xfcb2,		/* PWM50T2 */
	0xfcba,		/* PWM51T2 */
	0xfcc2,		/* PWM52T2 */
	0xfcca,		/* PWM53T2 */
	0xfcd2,		/* PWM54T2 */
	0xfcda,		/* PWM55T2 */
	0xfce2,		/* PWM56T2 */
	0xfcea,		/* PWM57T2 */
};

u16 code PWMxHLD[48] = {
	0xff15,		/* PWM00HLD */
	0xff1d,		/* PWM01HLD */
	0xff25,		/* PWM02HLD */
	0xff2d,		/* PWM03HLD */
	0xff35,		/* PWM04HLD */
	0xff3d,		/* PWM05HLD */
	0xff45,		/* PWM06HLD */
	0xff4d,		/* PWM07HLD */
	0xff65,		/* PWM10HLD */
	0xff6d,		/* PWM11HLD */
	0xff75,		/* PWM12HLD */
	0xff7d,		/* PWM13HLD */
	0xff85,		/* PWM14HLD */
	0xff8d,		/* PWM15HLD */
	0xff95,		/* PWM16HLD */
	0xff9d,		/* PWM17HLD */
	0xffb5,		/* PWM20HLD */
	0xffbd,		/* PWM21HLD */
	0xffc5,		/* PWM22HLD */
	0xffcd,		/* PWM23HLD */
	0xffd5,		/* PWM24HLD */
	0xffdd,		/* PWM25HLD */
	0xffe5,		/* PWM26HLD */
	0xffed,		/* PWM27HLD */
	0xfc15,		/* PWM30HLD */
	0xfc1d,		/* PWM31HLD */
	0xfc25,		/* PWM32HLD */
	0xfc2d,		/* PWM33HLD */
	0xfc35,		/* PWM34HLD */
	0xfc3d,		/* PWM35HLD */
	0xfc45,		/* PWM36HLD */
	0xfc4d,		/* PWM37HLD */
	0xfc65,		/* PWM40HLD */
	0xfc6d,		/* PWM41HLD */
	0xfc75,		/* PWM42HLD */
	0xfc7d,		/* PWM43HLD */
	0xfc85,		/* PWM44HLD */
	0xfc8d,		/* PWM45HLD */
	0xfc95,		/* PWM46HLD */
	0xfc9d,		/* PWM47HLD */
	0xfcb5,		/* PWM50HLD */
	0xfcbd,		/* PWM51HLD */
	0xfcc5,		/* PWM52HLD */
	0xfccd,		/* PWM53HLD */
	0xfcd5,		/* PWM54HLD */
	0xfcdd,		/* PWM55HLD */
	0xfce5,		/* PWM56HLD */
	0xfced,		/* PWM57HLD */
};

//========================================================================
// ����: u8 PWMChannelCtrl(u8 PWM_id, u8 pwm_eno, u8 pwm_ini, u8 pwm_eni, u8 pwm_ent2i, u8 pwm_ent1i)
// ����: PWMͨ�����ƼĴ�������. 
// ����: PWM_id: PWMͨ�����. ȡֵ 0~57
//			 pwm_eno:   pwm���ʹ��, 0��ΪGPIO, 1��ΪPWM���.
//			 pwm_ini:   pwm����˵ĳ�ʼ��ƽ, 0Ϊ�͵�ƽ, 1Ϊ�ߵ�ƽ.
//			 pwm_eni:   pwmͨ���ж�ʹ�ܿ���, 0Ϊ�ر�PWM�ж�, 1Ϊʹ��PWM�ж�.
//			 pwm_ent2i: pwmͨ���ڶ����������ж�ʹ�ܿ���, 0Ϊ�ر�PWM�ڶ����������ж�, 1Ϊʹ��PWM�ڶ����������ж�.
//			 pwm_ent1i: pwmͨ����һ���������ж�ʹ�ܿ���, 0Ϊ�ر�PWM��һ���������ж�, 1Ϊʹ��PWM��һ���������ж�.
// ����: 0:��ȷ, 2:����.
// �汾: V1.0, 2020-09-22
//========================================================================
u8	PWMChannelCtrl(u8 PWM_id, u8 pwm_eno, u8 pwm_ini, u8 pwm_eni, u8 pwm_ent2i, u8 pwm_ent1i)
{
	u8	xdata *pPWMxCR;
	
	if(PWM_id > PWM57)	return 2;	//id����
	if(pwm_eno > 1)	return 2;	//���ʹ�ܴ���
	if(pwm_ini > 1)	return 2;	//����˵ĳ�ʼ��ƽ����
	if(pwm_eni > 1)	return 2;	//�ж�ʹ�ܿ��ƴ���
	if(pwm_ent2i > 1)	return 2;	//�ڶ����������ж�ʹ�ܿ��ƴ���
	if(pwm_ent1i > 1)	return 2;	//��һ���������ж�ʹ�ܿ��ƴ���
	
	EAXSFR();		/* MOVX A,@DPTR/MOVX @DPTR,Aָ��Ĳ�������Ϊ��չSFR(XSFR) */
	pPWMxCR = (u8 *)PWMxCR[PWM_id];
	*pPWMxCR = (pwm_eno << 7) | (pwm_ini << 6) | (pwm_eni << 2)| (pwm_ent2i << 1)| pwm_ent1i;
	EAXRAM();		/* MOVX A,@DPTR/MOVX @DPTR,Aָ��Ĳ�������Ϊ��չRAM(XRAM) */
	return 0;
}

//========================================================================
// ����: u8 PWMPeriodDuty(u8 PWM_id, u16 Period, u16 dutyL, u16 dutyH)
// ����: PWM����, ռ�ձ�����. 
// ����: PWM_id:  PWMͨ�����. ȡֵ 0~57
//			 dutyL:   pwm����͵�ƽλ��, ȡֵ 0~0x7fff.
//			 dutyH:   pwm����ߵ�ƽλ��, ȡֵ 0~0x7fff.
// ����: 0:��ȷ, 2:����.
// �汾: V1.0, 2020-09-22
//========================================================================
u8	PWM15Duty(u8 PWM_id, u16 dutyL, u16 dutyH)
{
	u16	xdata *pPWMxT1;
	u16	xdata *pPWMxT2;
	
	if(PWM_id > PWM57)	return 2;	//id����
	if(dutyL > 0x7fff)	return 2;	//�͵�ƽʱ�����ô���
	if(dutyH > 0x7fff)	return 2;	//�ߵ�ƽʱ�����ô���
	
	EAXSFR();		/* MOVX A,@DPTR/MOVX @DPTR,Aָ��Ĳ�������Ϊ��չSFR(XSFR) */
	pPWMxT1 = (u16 *)PWMxT1[PWM_id];
	*pPWMxT1 = dutyL & 0x7fff;

	pPWMxT2 = (u16 *)PWMxT2[PWM_id];
	*pPWMxT2 = dutyH & 0x7fff;
	EAXRAM();		/* MOVX A,@DPTR/MOVX @DPTR,Aָ��Ĳ�������Ϊ��չRAM(XRAM) */
	return 0;
}

//========================================================================
// ����: u8 PWMOutputSet(u8 PWM_id, u8 pwm_hldl, u8 pwm_hldh)
// ����: PWMͨ�����ƼĴ�������. 
// ����: PWM_id: PWMͨ�����. ȡֵ 0~57
//			 pwm_hldl:   pwmǿ������͵�ƽ����λ, 0�������, 1ǿ������͵�ƽ.
//			 pwm_hldh:   pwmǿ������ߵ�ƽ����λ, 0�������, 1ǿ������ߵ�ƽ.
// ����: 0:��ȷ, 2:����.
// �汾: V1.0, 2020-09-22
//========================================================================
u8	PWMLevelSet(u8 PWM_id, u8 pwm_hldl, u8 pwm_hldh)
{
	u8	xdata *pPWMxHLD;
	
	if(PWM_id > PWM57)	return 2;	//id����
	if(pwm_hldh > 1)	return 2;	//���ʹ�ܴ���
	if(pwm_hldl > 1)	return 2;	//����˵ĳ�ʼ��ƽ����
	
	EAXSFR();		/* MOVX A,@DPTR/MOVX @DPTR,Aָ��Ĳ�������Ϊ��չSFR(XSFR) */
	pPWMxHLD = (u8 *)PWMxHLD[PWM_id];
	*pPWMxHLD = (pwm_hldh << 1) | pwm_hldl;
	EAXRAM();		/* MOVX A,@DPTR/MOVX @DPTR,Aָ��Ĳ�������Ϊ��չRAM(XRAM) */
	return 0;
}

//========================================================================
// ����: void	PWM15_Init(u8 PWM_id, PWM15_InitTypeDef *PWMx)
// ����: 15λ��ǿ��PWM��ʼ������.
// ����: PWM_id: PWM���. ȡֵ PWM0,PWM1,PWM2,PWM3,PWM4,PWM5
//		 PWMx: �ṹ����,��ο�ͷ�ļ���Ķ���.
// ����: none.
// �汾: V1.0, 2020-09-22
//========================================================================
void	PWM15_Init(u8 PWM_id, PWM15_InitTypeDef *PWMx)
{
	if(PWM_id > PWM5)	return;		//id����

	EAXSFR();		/* MOVX A,@DPTR/MOVX @DPTR,Aָ��Ĳ�������Ϊ��չSFR(XSFR) */
	if(PWM_id == PWM0)
	{
		if(PWMx->PWM_Enable == ENABLE)	 PWM15_PWM0_Enable();	//ʹ��PWM0
		else		PWM15_PWM0_Disable();	//�ر�PWM0
		PWM0_PS_Set(PWMx->PWM_Clock_PS);	//ϵͳʱ�ӷ�Ƶ����,  0~15
		PWM0C = PWMx->PWM_Period & 0x7fff;
		if(PWMx->PWM_Counter == ENABLE)	 PWM15_Counter0_Enable();	//ʹ�ܼ�����
		else		PWM15_Counter0_Disable();	//�رռ�����
	}
	
	if(PWM_id == PWM1)
	{
		if(PWMx->PWM_Enable == ENABLE)	 PWM15_PWM1_Enable();	//ʹ��PWM1
		else		PWM15_PWM1_Disable();	//�ر�PWM1
		PWM1_PS_Set(PWMx->PWM_Clock_PS);	//ϵͳʱ�ӷ�Ƶ����,  0~15
		PWM1C = PWMx->PWM_Period & 0x7fff;
		if(PWMx->PWM_Counter == ENABLE)	 PWM15_Counter1_Enable();	//ʹ�ܼ�����
		else		PWM15_Counter1_Disable();	//�رռ�����
	}
	
	if(PWM_id == PWM2)
	{
		if(PWMx->PWM_Enable == ENABLE)	 PWM15_PWM2_Enable();	//ʹ��PWM2
		else		PWM15_PWM2_Disable();	//�ر�PWM2
		PWM2_PS_Set(PWMx->PWM_Clock_PS);	//ϵͳʱ�ӷ�Ƶ����,  0~15
		PWM2C = PWMx->PWM_Period & 0x7fff;
		if(PWMx->PWM_Counter == ENABLE)	 PWM15_Counter2_Enable();	//ʹ�ܼ�����
		else		PWM15_Counter2_Disable();	//�رռ�����
	}
	
	if(PWM_id == PWM3)
	{
		if(PWMx->PWM_Enable == ENABLE)	 PWM15_PWM3_Enable();	//ʹ��PWM3
		else		PWM15_PWM3_Disable();	//�ر�PWM3
		PWM3_PS_Set(PWMx->PWM_Clock_PS);	//ϵͳʱ�ӷ�Ƶ����,  0~15
		PWM3C = PWMx->PWM_Period & 0x7fff;
		if(PWMx->PWM_Counter == ENABLE)	 PWM15_Counter3_Enable();	//ʹ�ܼ�����
		else		PWM15_Counter3_Disable();	//�رռ�����
	}
	
	if(PWM_id == PWM4)
	{
		if(PWMx->PWM_Enable == ENABLE)	 PWM15_PWM4_Enable();	//ʹ��PWM4
		else		PWM15_PWM4_Disable();	//�ر�PWM4
		PWM4_PS_Set(PWMx->PWM_Clock_PS);	//ϵͳʱ�ӷ�Ƶ����,  0~15
		PWM4C = PWMx->PWM_Period & 0x7fff;
		if(PWMx->PWM_Counter == ENABLE)	 PWM15_Counter4_Enable();	//ʹ�ܼ�����
		else		PWM15_Counter4_Disable();	//�رռ�����
	}
	
	if(PWM_id == PWM5)
	{
		if(PWMx->PWM_Enable == ENABLE)	 PWM15_PWM5_Enable();	//ʹ��PWM5
		else		PWM15_PWM5_Disable();	//�ر�PWM5
		PWM5_PS_Set(PWMx->PWM_Clock_PS);	//ϵͳʱ�ӷ�Ƶ����,  0~15
		PWM5C = PWMx->PWM_Period & 0x7fff;
		if(PWMx->PWM_Counter == ENABLE)	 PWM15_Counter5_Enable();	//ʹ�ܼ�����
		else		PWM15_Counter5_Disable();	//�رռ�����
	}
	EAXRAM();		/* MOVX A,@DPTR/MOVX @DPTR,Aָ��Ĳ�������Ϊ��չRAM(XRAM) */
}


//========================================================================
// ����: void	PWM0_Handler (void) interrupt PWM0_VECTOR
// ����: PWM0�жϴ������.
// ����: None
// ����: none.
// �汾: V1.0, 2020-10-13
//========================================================================
void	PWM0_Handler (void) interrupt PWM0_VECTOR
{
	char store;
	store = P_SW2;
	P_SW2 |= 0x80;

	if(PWMCFG01 & 0x08)		//PWM0�ж�
	{
		PWMCFG01 &= ~0x08;		//��PWM0�жϱ�־
		// TODO: �ڴ˴�����û�����
	}
	if(PWM0IF)
	{
		PWM0IF = 0;
		P27 = ~P27;
	}
	P_SW2 = store;
}
//========================================================================
// ����: void	PWM1_Handler (void) interrupt PWM1_VECTOR
// ����: PWM1�жϴ������.
// ����: None
// ����: none.
// �汾: V1.0, 2020-10-13
//========================================================================
void	PWM1_Handler (void) interrupt PWM1_VECTOR
{
	char store;
	store = P_SW2;
	P_SW2 |= 0x80;

	if(PWMCFG01 & 0x80)		//PWM1�ж�
	{
		PWMCFG01 &= ~0x80;		//��PWM1�жϱ�־
		// TODO: �ڴ˴�����û�����
	}
	if(PWM1IF)
	{
		PWM1IF = 0;
		P26 = ~P26;
	}
	P_SW2 = store;
}
//========================================================================
// ����: void	PWM2_Handler (void) interrupt PWM2_VECTOR
// ����: PWM2�жϴ������.
// ����: None
// ����: none.
// �汾: V1.0, 2020-10-13
//========================================================================
void	PWM2_Handler (void) interrupt PWM2_VECTOR
{
	char store;
	store = P_SW2;
	P_SW2 |= 0x80;

	if(PWMCFG23 & 0x08)		//PWM2�ж�
	{
		PWMCFG23 &= ~0x08;		//��PWM2�жϱ�־
		// TODO: �ڴ˴�����û�����
	}
	if(PWM2IF)
	{
		PWM2IF = 0;
		P25 = ~P25;
	}
	P_SW2 = store;
}
//========================================================================
// ����: void	PWM3_Handler (void) interrupt PWM3_VECTOR
// ����: PWM3�жϴ������.
// ����: None
// ����: none.
// �汾: V1.0, 2020-10-13
//========================================================================
void	PWM3_Handler (void) interrupt PWM3_VECTOR
{
	char store;
	store = P_SW2;
	P_SW2 |= 0x80;

	if(PWMCFG23 & 0x80)		//PWM3�ж�
	{
		PWMCFG23 &= ~0x80;		//��PWM3�жϱ�־
		// TODO: �ڴ˴�����û�����
	}
	if(PWM3IF)
	{
		PWM3IF = 0;
		P24 = ~P24;
	}
	P_SW2 = store;
}
//========================================================================
// ����: void	PWM4_Handler (void) interrupt PWM4_VECTOR
// ����: PWM4�жϴ������.
// ����: None
// ����: none.
// �汾: V1.0, 2020-10-13
//========================================================================
void	PWM4_Handler (void) interrupt PWM4_VECTOR
{
	char store;
	store = P_SW2;
	P_SW2 |= 0x80;

	if(PWMCFG45 & 0x08)		//PWM4�ж�
	{
		PWMCFG45 &= ~0x08;		//��PWM4�жϱ�־
		// TODO: �ڴ˴�����û�����
	}
	if(PWM4IF)
	{
		PWM4IF = 0;
		P23 = ~P23;
	}
	P_SW2 = store;
}
//========================================================================
// ����: void	PWM5_Handler (void) interrupt PWM5_VECTOR
// ����: PWM5�жϴ������.
// ����: None
// ����: none.
// �汾: V1.0, 2020-10-13
//========================================================================
//void	PWM5_Handler (void) interrupt PWM5_VECTOR	//�ж������ų���31���ɽ��������жϺ���ת�����������������
//{
//	if(PWMCFG45 & 0x80)		//PWM5�ж�
//	{
//		PWMCFG45 &= ~0x80;		//��PWM5�жϱ�־
//		// TODO: �ڴ˴�����û�����
//	}
//}
