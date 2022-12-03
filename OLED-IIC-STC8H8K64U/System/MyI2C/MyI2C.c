#include "MyI2C.h"

#include "OLED.h"

void I2C_GPIO_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	GPIO_InitStructure.Pin	= SDA_Pin|SCL_Pin;		// I2C.SDA I2C.SCL
	GPIO_InitStructure.Mode	= GPIO_PullUp;			// 准双向口
	GPIO_Inilize(IIC_GPIO_Port, &GPIO_InitStructure);
}

void I2C_Config(void)
{
	I2C_InitTypeDef I2C_InitStructure;
	I2C_InitStructure.I2C_Mode      = I2C_Mode_Master;	//主从选择 I2C_Mode_Master, I2C_Mode_Slave
	I2C_InitStructure.I2C_Enable    = ENABLE;			//I2C功能使能, ENABLE, DISABLE
	I2C_InitStructure.I2C_MS_WDTA   = DISABLE;			//主机使能自动发送, ENABLE, DISABLE
	I2C_InitStructure.I2C_MS_Interrupt = DISABLE;		//使能主机模式中断, ENABLE, DISABLE
	I2C_InitStructure.I2C_Speed     = 0;				//总线速度=Fosc/2/(Speed*2+4), 0~63
	I2C_InitStructure.I2C_IoUse     = I2C_P24_P25;		//IO口切换 I2C_P14_P15, I2C_P24_P25, I2C_P33_P32

	I2C_Init(&I2C_InitStructure);
}

void My_I2C_Init(void)
{
	I2C_GPIO_Config();
	I2C_Config();
}

//========================================================================
// 函数: void IIC_WR_Byte(u8 buf, u8 cmd)
// 描述: I2C写入数据函数.
// 参数: buf写入数据, cmd写入数据或命令.
// 返回: none.
// 版本: V1.0, 2020-09-15
//========================================================================
void IIC_WR_Byte(u8 buf, u8 cmd)
{
	EAXSFR();		/* MOVX A,@DPTR/MOVX @DPTR,A指令的操作对象为扩展SFR(XSFR) */
	Start();                                //发送起始命令
	SendData(SLAVE_ADDRESS);                //发送设备地址+写命令
	RecvACK();
	if(cmd)			// 数据
	{
		SendData(OLED_DATA_CHR);
	}
	else			// 命令
	{
		SendData(OLED_CMD_CHR);
	}
	RecvACK();
	SendData(buf);
	RecvACK();
	Stop();                                 //发送停止命令
	EAXRAM();		/* MOVX A,@DPTR/MOVX @DPTR,A指令的操作对象为扩展RAM(XRAM) */
}

//========================================================================
// 函数: void IIC_WR_Byte_Dat(u8 buf)
// 描述: I2C写入数据函数.
// 参数: buf写入数据
// 返回: none.
// 版本: V1.0, 2020-09-15
//========================================================================
void IIC_WR_Byte_Dat(u8 buf)
{
	EAXSFR();		/* MOVX A,@DPTR/MOVX @DPTR,A指令的操作对象为扩展SFR(XSFR) */
	Start();                                //发送起始命令
	SendData(SLAVE_ADDRESS);                //发送设备地址+写命令
	RecvACK();
	SendData(OLED_DATA_CHR);
	RecvACK();
	SendData(buf);
	RecvACK();
	Stop();                                 //发送停止命令
	EAXRAM();		/* MOVX A,@DPTR/MOVX @DPTR,A指令的操作对象为扩展RAM(XRAM) */
}

//========================================================================
// 函数: void IIC_WR_Byte_Cmd(u8 buf)
// 描述: I2C写入命令函数.
// 参数: buf写入命令
// 返回: none.
// 版本: V1.0, 2020-09-15
//========================================================================
void IIC_WR_Byte_Cmd(u8 buf)
{
	EAXSFR();		/* MOVX A,@DPTR/MOVX @DPTR,A指令的操作对象为扩展SFR(XSFR) */
	Start();                                //发送起始命令
	SendData(SLAVE_ADDRESS);                //发送设备地址+写命令
	RecvACK();
	SendData(OLED_CMD_CHR);
	RecvACK();
	SendData(buf);
	RecvACK();
	Stop();                                 //发送停止命令
	EAXRAM();		/* MOVX A,@DPTR/MOVX @DPTR,A指令的操作对象为扩展RAM(XRAM) */
}

//========================================================================
// 函数: void IIC_WR_Byte_Fast(u8 *buf, u16 size, u8 cmd)
// 描述: I2C写入数据函数.
// 参数: *buf写入数据, size写入数据个数，cmd写入数据或命令.
// 返回: none.
// 版本: V1.0, 2020-09-15
//========================================================================
void IIC_WR_Byte_Fast(u8 *buf, u16 size, u8 cmd)
{
	EAXSFR();		/* MOVX A,@DPTR/MOVX @DPTR,A指令的操作对象为扩展SFR(XSFR) */
	Start();                                //发送起始命令
	SendData(SLAVE_ADDRESS);                //发送设备地址+写命令
	RecvACK();
	if(cmd)			// 数据
	{
		SendData(OLED_DATA_CHR);
	}
	else			// 命令
	{
		SendData(OLED_CMD_CHR);
	}
	RecvACK();
	while(size--)
	{
		SendData(*buf++);
		RecvACK();
	}
	Stop();                                 //发送停止命令
	EAXRAM();		/* MOVX A,@DPTR/MOVX @DPTR,A指令的操作对象为扩展RAM(XRAM) */
}

//========================================================================
// 函数: void IIC_WR_Byte_Dat_Fast(u8 *buf, u16 size)
// 描述: I2C写入数据函数.
// 参数: *buf写入数据, size写入数据个数，cmd写入数据或命令.
// 返回: none.
// 版本: V1.0, 2020-09-15
//========================================================================
void IIC_WR_Byte_Dat_Fast(u8 *buf, u16 size)
{
	EAXSFR();		/* MOVX A,@DPTR/MOVX @DPTR,A指令的操作对象为扩展SFR(XSFR) */
	Start();                                //发送起始命令
	SendData(SLAVE_ADDRESS);                //发送设备地址+写命令
	RecvACK();
	SendData(OLED_DATA_CHR);
	RecvACK();
	while(size--)
	{
		SendData(*buf++);
		RecvACK();
	}
	Stop();                                 //发送停止命令
	EAXRAM();		/* MOVX A,@DPTR/MOVX @DPTR,A指令的操作对象为扩展RAM(XRAM) */
}

//========================================================================
// 函数: void IIC_WR_Byte_Cmd_Fast(u8 *buf, u16 size)
// 描述: I2C写入命令函数.
// 参数: *buf写入数据, size写入数据个数
// 返回: none.
// 版本: V1.0, 2020-09-15
//========================================================================
void IIC_WR_Byte_Cmd_Fast(u8 *buf, u16 size)
{
	EAXSFR();		/* MOVX A,@DPTR/MOVX @DPTR,A指令的操作对象为扩展SFR(XSFR) */
	Start();                                //发送起始命令
	SendData(SLAVE_ADDRESS);                //发送设备地址+写命令
	RecvACK();
	SendData(OLED_CMD_CHR);
	RecvACK();
	while(size--)
	{
		SendData(*buf++);
		RecvACK();
	}
	Stop();                                 //发送停止命令
	EAXRAM();		/* MOVX A,@DPTR/MOVX @DPTR,A指令的操作对象为扩展RAM(XRAM) */
}









