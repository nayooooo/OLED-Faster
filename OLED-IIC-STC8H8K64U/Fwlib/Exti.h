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

#ifndef	__EXTI_H
#define	__EXTI_H

#include	"config.h"

#define	EXT_INT0			0	//��ʼ�����ж�0
#define	EXT_INT1			1	//��ʼ�����ж�1
#define	EXT_INT2			2	//��ʼ�����ж�2
#define	EXT_INT3			3	//��ʼ�����ж�3
#define	EXT_INT4			4	//��ʼ�����ж�4

#define	EXT_MODE_RiseFall	0	//������/�½����ж�
#define	EXT_MODE_Fall			1	//�½����ж�

typedef struct
{
	u8	EXTI_Mode;			//�ж�ģʽ,  	EXT_MODE_RiseFall, EXT_MODE_Fall
	u8	EXTI_Priority;		//���ȼ�����		Priority_0,Priority_1,Priority_2,Priority_3
	u8	EXTI_Interrupt;	//�ж�����			ENABLE,DISABLE
} EXTI_InitTypeDef;

u8	Ext_Inilize(u8 EXT, EXTI_InitTypeDef *INTx);

#endif
