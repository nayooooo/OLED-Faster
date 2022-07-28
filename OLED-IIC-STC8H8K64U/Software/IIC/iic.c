/**
 * @file iic.c
 * @details 24.000MHz、1T
 * @chip STC8H8K64U
 */
#include "iic.h"
#include "delay.h"
#include "GPIO.h"

#include "oled.h"

/**********************************************
//		GND -> GND
//		VCC -> VCC
//		SDA -> P1.4
//		SCL -> P1.5
**********************************************/

/* 配置IIC接口 -------------------------------------*/
void IIC_GPIO_Config(void)
{					     
	GPIO_InitTypeDef GPIO_InitStructure;
	
	GPIO_InitStructure.Mode = GPIO_OUT_OD;		// 开漏输出
	GPIO_InitStructure.Pin = SDA_Pin|SCL_Pin;	// IIC_SDA IIC_SCL
	GPIO_Inilize(IIC_GPIO_Port, &GPIO_InitStructure);
}

/* IIC读写函数 -------------------------------------*/
/* 慢速读写 ----------------------------------------*/
void IIC_WR_Byte(u8 dat, u8 cmd)
{
	IIC_Start();
	IIC_Send_Byte(SLAVE_ADDRESS);            // Slave address
	IIC_Wait_Ack();	
	if(cmd)			// 数据
	{
		IIC_Send_Byte(OLED_DATA_CHR);
	}
	else			// 命令
	{
		IIC_Send_Byte(OLED_CMD_CHR);
	}
	IIC_Wait_Ack();
	IIC_Send_Byte(dat);
	IIC_Wait_Ack();
	IIC_Stop();
}

void IIC_WR_Byte_Dat(u8 dat)
{
	IIC_Start();
	IIC_Send_Byte(SLAVE_ADDRESS);            // Slave address
	IIC_Wait_Ack();
	IIC_Send_Byte(OLED_DATA_CHR);
	IIC_Wait_Ack();
	IIC_Send_Byte(dat);
	IIC_Wait_Ack();
	IIC_Stop();
}

void IIC_WR_Byte_Cmd(u8 cmd)
{
	IIC_Start();
	IIC_Send_Byte(SLAVE_ADDRESS);            // Slave address
	IIC_Wait_Ack();
	IIC_Send_Byte(OLED_CMD_CHR);
	IIC_Wait_Ack();
	IIC_Send_Byte(cmd);
	IIC_Wait_Ack();
	IIC_Stop();
}
/* 快速读写 ----------------------------------------*/
/**
 * @fn void IIC_WR_Byte_Fast(u8 dat, u8 cmd, u8 *buf)
 * @param[buf] 需要传输的数据数组的首地址
 * @param[size] 需要传输的数据数组的大小
 * @param[cmd] 需要传输的数据是数据/命令
 */
void IIC_WR_Byte_Fast(u8 *buf, u16 size, u8 cmd)
{
	IIC_Start();
	IIC_Send_Byte(SLAVE_ADDRESS);            // Slave address
	IIC_Wait_Ack();
	if(cmd)			// 数据
	{
		IIC_Send_Byte(OLED_DATA_CHR);
	}
	else			// 命令
	{
		IIC_Send_Byte(OLED_CMD_CHR);
	}
	IIC_Wait_Ack();
	while(size--){
		IIC_Send_Byte(*buf);
		IIC_Wait_Ack();
		buf++;
	}
	IIC_Stop();
}

/**
 * @fn void IIC_WR_Byte_Dat_Fast(u8 *Dat_Buf, u16 size)
 * @param[Dat_Buf] 需要传输的数据数组的首地址
 * @param[size] 需要传输的数据数组的大小
 */
void IIC_WR_Byte_Dat_Fast(u8 *Dat_Buf, u16 size)
{
	IIC_Start();
	IIC_Send_Byte(SLAVE_ADDRESS);            // Slave address
	IIC_Wait_Ack();
	IIC_Send_Byte(OLED_DATA_CHR);
	IIC_Wait_Ack();
	while(size--){
		IIC_Send_Byte(*Dat_Buf);
		IIC_Wait_Ack();
		Dat_Buf++;
	}
	IIC_Stop();
}


/**
 * @fn void IIC_WR_Byte_Cmd_Fast(u8 *Cmd_Buf, u16 size)
 * @param[Cmd_Buf] 需要传输的命令数组的首地址
 * @param[size] 需要传输的命令数组的大小
 */
void IIC_WR_Byte_Cmd_Fast(u8 *Cmd_Buf, u16 size)
{
	IIC_Start();
	IIC_Send_Byte(SLAVE_ADDRESS);            // Slave address
	IIC_Wait_Ack();
	IIC_Send_Byte(OLED_CMD_CHR);
	IIC_Wait_Ack();
	while(size--){
		IIC_Send_Byte(*Cmd_Buf);
		IIC_Wait_Ack();
	}
	IIC_Stop();
}


/* 本地协议函数 -----------------------------------*/
// IIC起始信号
static void IIC_Start(void)
{
	SDA_Clr();
	SCL_Clr();
 	NOP1();		// 适当延时，实际上延时了0.083us
 	SDA_Set();
 	NOP1();		// 需要延时0.6us，实际上延时了0.085us
	SCL_Set();
}

// IIC停止信号
static void IIC_Stop(void)
{
	SDA_Set();
	SCL_Clr();
 	NOP1();			// 需要延时0.6us，实际上延时了0.083us
	SDA_Clr();
 	delay_1_us(2);	// 需要延时1.3us，实际上延时了1.67us，参数为1时无法驱动
}

// IIC等待应答
static u8 IIC_Wait_Ack(void)
{
	u8 ucErrTime=0;
	SDA_IN();      // SDA输入
	SCL_Clr();
 	NOP1();	// 需要延时0.6us，实际上延时了0.083us
	while(READ_SDA)
	{
		ucErrTime++;
		if(ucErrTime>250)
		{
			IIC_Stop();
			return 1;
		}
	}
	SCL_Set();
	return 0;  
}

// IIC发送一字节
static void IIC_Send_Byte(u8 txd)
{                        
    u8 t;
//    SCL_Set();  // 起始信号后时钟线已经被拉低了
    for(t=0;t<8;t++)
    {
        IIC_SDA=(txd&0x80);
        txd<<=1;
		SCL_Clr();
		NOP4();	// 需要延时2.5us，实际上延时了0.332us
		SCL_Set();
    }
}