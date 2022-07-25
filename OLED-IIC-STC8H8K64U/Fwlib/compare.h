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

#ifndef	__COMPARE_H
#define	__COMPARE_H

#include	"config.h"

//CMPCR1
#define	CMPEN	0x80	//1: ����Ƚ���, 0: ��ֹ,�رձȽ�����Դ
#define	CMPIF	0x40	//�Ƚ����жϱ�־, ���������ػ��½����ж�, �����0
#define	PIE		0x20	//1: �ȽϽ����0��1, �����������ж�
#define	NIE		0x10	//1: �ȽϽ����1��0, �����½����ж�
#define	PIS		0x08	//����������ѡ��, 0: ѡ���ڲ�P5.5��������,           1: ��ADCIS[2:0]��ѡ���ADC�������������.
#define	NIS		0x04	//���븺����ѡ��, 0: ѡ���ڲ�BandGap��ѹBGv��������, 1: ѡ���ⲿP5.4������.
#define	CMPOE	0x02	//1: ����ȽϽ�������P1.2, 0: ��ֹ.
#define	CMPRES	0x01	//�ȽϽ��, 1: CMP+��ƽ����CMP-,  0: CMP+��ƽ����CMP-,  ֻ��

//CMPCR2
#define	INVCMPO	0x80	//1: �Ƚ������ȡ��,  0: ��ȡ��
#define	DISFLT	0x40	//1: �ر�0.1uF�˲�,   0: ����
#define	LCDTY		0x00	//0~63, �ȽϽ���仯��ʱ������

#define	CMP_OUT_P34	(0<<3)
#define	CMP_OUT_P41	(1<<3)

typedef struct
{ 
	u8	CMP_EN;					//�Ƚ���������ֹ, 			ENABLE,DISABLE
	u8	CMP_Interrupt;	//�Ƚ����ж�������ֹ, 	ENABLE,DISABLE
	u8	CMP_RiseInterruptEn;	//�Ƚ����������ж�������ֹ, 	ENABLE,DISABLE       
	u8	CMP_FallInterruptEn;	//�Ƚ����½����ж�������ֹ, 	ENABLE,DISABLE
	u8	CMP_P_Select;		//�Ƚ�������������ѡ��, CMP_P_P37: ѡ���ڲ�P3.7��������, CMP_P_ADC: ��ADCIS[2:0]��ѡ���ADC�������������.
	u8	CMP_N_Select;		//�Ƚ������븺����ѡ��, CMP_N_GAP: ѡ���ڲ�BandGap��ѹBGv��������, CMP_N_P36: ѡ���ⲿP3.6������.
	u8	CMP_Outpt_En;		//����ȽϽ�����,   ENABLE,DISABLE
	u8	CMP_Priority;			//ָ���ж����ȼ�(�͵���) Priority_0,Priority_1,Priority_2,Priority_3
	u8	CMP_InvCMPO;		//�Ƚ������ȡ��, ENABLE,DISABLE
	u8	CMP_100nsFilter;	//�ڲ�0.1uF�˲�,  ENABLE,DISABLE
	u8	CMP_OutDelayDuty;	//0~63, �ȽϽ���仯��ʱ������
	u8	CMP_P_SW;				//ѡ��P3.4/P4.1��Ϊ�Ƚ��������,  CMP_OUT_P34,CMP_OUT_P41
} CMP_InitDefine; 

void	CMP_Inilize(CMP_InitDefine *CMPx);

#endif
