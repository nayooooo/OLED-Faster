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

#ifndef	__I2C_H
#define	__I2C_H

#include	"config.h"

#define	I2C_BUF_LENTH	128
#define	I2C_BUF_type	xdata


#define	I2C_Mode_Master			1
#define	I2C_Mode_Slave			0

#define	I2C_P14_P15					(0<<4)
#define	I2C_P24_P25					(1<<4)
#define	I2C_P33_P32					(3<<4)

typedef struct
{
	u8	I2C_Speed;				//�����ٶ�=Fosc/2/(Speed*2+4),      0~63
	u8	I2C_Enable;				//I2C����ʹ��,   ENABLE, DISABLE
	u8	I2C_Mode;					//����ģʽѡ��,  I2C_Mode_Master,I2C_Mode_Slave
	u8	I2C_MS_Interrupt;	//ʹ������ģʽ�ж�,  ENABLE, DISABLE
	u8	I2C_MS_WDTA;				//����ʹ���Զ�����,  ENABLE, DISABLE

	u8	I2C_SL_ESTAI;			//�ӻ�����START�ź��ж�ʹ��,  ENABLE, DISABLE
	u8	I2C_SL_ERXI;			//�ӻ�����1�ֽ������ж�ʹ��,  ENABLE, DISABLE
	u8	I2C_SL_ETXI;			//�ӻ�����1�ֽ������ж�ʹ��,  ENABLE, DISABLE
	u8	I2C_SL_ESTOI;			//�ӻ�����STOP�ź��ж�ʹ��,  ENABLE, DISABLE

	u8	I2C_SL_ADR;				//�ӻ��豸��ַ,  0~127
	u8	I2C_SL_MA;				//�ӻ��豸��ַ�Ƚ�ʹ��,  ENABLE, DISABLE

	u8	I2C_IoUse;				//I2C_P14_P15, I2C_P24_P25, I2C_P33_P32
} I2C_InitTypeDef;


extern	u8 	I2C_BUF_type I2C_RxBuffer[I2C_BUF_LENTH];


void	I2C_Init(I2C_InitTypeDef *I2Cx);
void	WriteNbyte(u8 addr, u8 *p, u8 number);
void	ReadNbyte( u8 addr, u8 *p, u8 number);

#endif

