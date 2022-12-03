#ifndef __MYI2C_H
#define __MYI2C_H

#include "config.h"
#include "I2C.h"
#include "GPIO.h"

/* I2C端口宏 ------------------------------------*/
#define IIC_GPIO_Port	GPIO_P2
#define SDA_Pin			GPIO_Pin_4
#define SCL_Pin			GPIO_Pin_5
#define IIC_SDA			P24
#define IIC_SCL			P25

/* I2C相关函数 ------------------------------*/
void I2C_GPIO_Config(void);
void I2C_Config(void);
void My_I2C_Init(void);

void IIC_WR_Byte(u8 buf, u8 cmd);
void IIC_WR_Byte_Dat(u8 buf);
void IIC_WR_Byte_Cmd(u8 buf);
void IIC_WR_Byte_Fast(u8 *buf, u16 size, u8 cmd);
void IIC_WR_Byte_Dat_Fast(u8 *buf, u16 size);
void IIC_WR_Byte_Cmd_Fast(u8 *buf, u16 size);

#endif /* __MYI2C_H */









