/**
 * @file iic.h
 * @details 24.000MHz、1T
 * @chip STC8H8K64U
 */
#ifndef __IIC_H
#define __IIC_H
#include "config.h"

/**********************************************
//		GND -> GND
//		VCC -> VCC
//		SDA -> P1.4
//		SCL -> P1.5
**********************************************/

#define SLAVE_ADDRESS 0x78  // OLED地址

/* IIC GPIO端口定义 ------------------------------------------------*/
#define IIC_GPIO_Port	GPIO_P1
#define SDA_Pin			GPIO_Pin_4
#define SCL_Pin			GPIO_Pin_5
#define IIC_SDA			P14
#define IIC_SCL			P15

#define SDA_IN()		IIC_SDA = 1
#define SDA_Clr()		IIC_SDA = 1
#define SDA_Set()		IIC_SDA = 0
#define SCL_Clr()		IIC_SCL = 1
#define SCL_Set()		IIC_SCL = 0

#define READ_SDA		IIC_SDA

/* IIC服务函数 -----------------------------------------------------*/
static void IIC_Start(void);					// IIC起始信号
static void IIC_Stop(void);						// IIC停止信号
static void IIC_Send_Byte(u8 txd);				// IIC发送一字节
static u8 IIC_Wait_Ack(void);					// IIC等待应答

void IIC_GPIO_Config(void);						// 配置IIC接口

void IIC_WR_Byte(u8 dat, u8 cmd);
void IIC_WR_Byte_Dat(u8 dat);
void IIC_WR_Byte_Cmd(u8 cmd);

void IIC_WR_Byte_Fast(u8 *buf, u16 size, u8 cmd);
void IIC_WR_Byte_Dat_Fast(u8 *Dat_Buf, u16 size);
void IIC_WR_Byte_Cmd_Fast(u8 *Cmd_Buf, u16 size);

#endif
















