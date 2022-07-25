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

/*************	����˵��	**************

���ļ�ΪSTC8ϵ�е����жϳ�ʼ�����жϳ���,�û�����������ļ����޸��Լ���Ҫ���жϳ���.

******************************************/

#include	"Exti.h"

/*************  �ⲿ�����ͱ������� *****************/
extern u8 WakeUpSource;


/********************* INT0�жϺ��� *************************/
void Ext_INT0 (void) interrupt INT0_VECTOR		//���ж�ʱ�Ѿ������־
{
//	P00 = ~P00;
	WakeUpSource = 1;
}

/********************* INT1�жϺ��� *************************/
void Ext_INT1 (void) interrupt INT1_VECTOR		//���ж�ʱ�Ѿ������־
{
//	P01 = ~P01;
	WakeUpSource = 2;
}

/********************* INT2�жϺ��� *************************/
void Ext_INT2 (void) interrupt INT2_VECTOR	//
{
//	P02 = ~P02;
	WakeUpSource = 3;
}

/********************* INT3�жϺ��� *************************/
void Ext_INT3 (void) interrupt INT3_VECTOR
{
//	P03 = ~P03;
	WakeUpSource = 4;
}

/********************* INT4�жϺ��� *************************/
void Ext_INT4 (void) interrupt INT4_VECTOR
{
//	P04 = ~P04;
	WakeUpSource = 5;
}

//========================================================================
// ����: u8	Ext_Inilize(u8 EXT, EXTI_InitTypeDef *INTx)
// ����: �ⲿ�жϳ�ʼ������.
// ����: INTx: �ṹ����,��ο�Exti.h��Ķ���.
// ����: �ɹ�����0, �ղ�������1,���󷵻�2.
// �汾: V1.0, 2012-10-22
//========================================================================
u8	Ext_Inilize(u8 EXT, EXTI_InitTypeDef *INTx)
{
	if(EXT >  EXT_INT4)	return 1;	//�ղ���
	
	if(EXT == EXT_INT0)	//���ж�0
	{
		IE0  = 0;	//���ж�0��־λ
		if(INTx->EXTI_Interrupt == ENABLE)		EX0 = 1;	//�����ж�
		else									EX0 = 0;	//��ֹ�ж�
		if(INTx->EXTI_Priority > Priority_3)	return 2;	//����
		INT0_Priority(INTx->EXTI_Priority);	//ָ���ж����ȼ�(�͵���) Priority_0,Priority_1,Priority_2,Priority_3
		if(INTx->EXTI_Mode == EXT_MODE_Fall)	IT0 = 1;	//�½����ж�
		else									IT0 = 0;	//����,�½����ж�
		return	0;		//�ɹ�
	}

	if(EXT == EXT_INT1)	//���ж�1
	{
		IE1  = 0;	//���ж�1��־λ
		if(INTx->EXTI_Interrupt == ENABLE)		EX1 = 1;	//�����ж�
		else									EX1 = 0;	//��ֹ�ж�
		if(INTx->EXTI_Priority > Priority_3)	return 2;	//����
		INT1_Priority(INTx->EXTI_Priority);	//ָ���ж����ȼ�(�͵���) Priority_0,Priority_1,Priority_2,Priority_3
		if(INTx->EXTI_Mode == EXT_MODE_Fall)	IT1 = 1;	//�½����ж�
		else									IT1 = 0;	//����,�½����ж�
		return	0;		//�ɹ�
	}

	if(EXT == EXT_INT2)		//���ж�2, �̶�Ϊ�½��ص����ȼ��ж�
	{
		if(INTx->EXTI_Interrupt == ENABLE)	INT_CLKO |=  (1 << 4);	//�����ж�	
		else								INT_CLKO &= ~(1 << 4);	//��ֹ�ж�
		return	0;		//�ɹ�
	}

	if(EXT == EXT_INT3)		//���ж�3, �̶�Ϊ�½��ص����ȼ��ж�
	{
		if(INTx->EXTI_Interrupt == ENABLE)	INT_CLKO |=  (1 << 5);	//�����ж�	
		else								INT_CLKO &= ~(1 << 5);	//��ֹ�ж�
		return	0;		//�ɹ�
	}

	if(EXT == EXT_INT4)		//���ж�4, �̶�Ϊ�½��ص����ȼ��ж�
	{
		if(INTx->EXTI_Interrupt == ENABLE)	INT_CLKO |=  (1 << 6);	//�����ж�	
		else								INT_CLKO &= ~(1 << 6);	//��ֹ�ж�
		return	0;		//�ɹ�
	}
	return 2;	//ʧ��
}
