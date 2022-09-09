#ifndef __IIC_H
#define __IIC_H
#include "sys.h"
/**********************************************
//		GND -> GND
//		VCC -> VCC
//		SCL -> GPIOB6
//		SDA -> GPIOB7
**********************************************/

#define SLAVE_ADDRESS 0x78

//IO输入输出切换
 
#define SDA_IN()  {GPIOB->CRL&=0X0FFFFFFF;GPIOB->CRL|=(u32)8<<28;}
#define SDA_OUT() {GPIOB->CRL&=0X0FFFFFFF;GPIOB->CRL|=(u32)3<<28;}

//IO口功能宏定义	 
#define IIC_SCL    PBout(6) //SCL
#define IIC_SDA    PBout(7) //SDA	 
#define READ_SDA   PBin(7)  //读SDA 

static void IIC_Start(void);
static void IIC_Stop(void);
static void IIC_Send_Byte(u8 txd);
static u8 IIC_Wait_Ack(void);  

void IIC_GPIO_Init(void);
void IIC_WR_Byte(u8 dat, u8 cmd);
void IIC_WR_Byte_Dat(u8 dat);
void IIC_WR_Byte_Cmd(u8 dat);
void IIC_WR_Byte_Fast(u8 *buf, u16 size, u8 cmd);
void IIC_WR_Byte_Dat_Fast(u8 *buf, u16 size);
void IIC_WR_Byte_Cmd_Fast(u8 *buf, u16 size);

#endif
















