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
	delay_5_us(1);
 	SDA_Set();
	delay_5_us(1);
	SCL_Set();
}	  

// IIC停止信号
static void IIC_Stop(void)
{
	SCL_Set();
	SDA_Set();
	SCL_Clr();
 	NOP2();		// 需要延时0.6us，实际上延时了0.83us
	SDA_Clr();
 	NOP4();		// 需要延时1.3us，实际上延时了1.67us
}

// IIC等待应答
static u8 IIC_Wait_Ack(void)
{
	u8 ucErrTime=0;
	SDA_IN();      // SDA输入
	SCL_Clr();
	NOP1();	// 需要延时us，实际上延时了0.42us
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

// IIC应答
static void IIC_Ack(void)
{
	SCL_Set();
	SDA_Set();
	delay_1_us(3);		// 需要延时2us，实际上延时了2.5us
	SCL_Clr();
	delay_1_us(3);		// 需要延时2us，实际上延时了2.5us
	SCL_Set();
}

// IIC不应答
static void IIC_NAck(void)
{
	SCL_Set();
	SDA_Clr();
	delay_1_us(3);		// 需要延时2us，实际上延时了2.5us
	SCL_Clr();
	delay_1_us(3);		// 需要延时2us，实际上延时了2.5us
	SCL_Set();
}

// IIC发送一字节
static void IIC_Send_Byte(u8 txd)
{                        
    u8 t;
//    IIC_SCL=0;  // 起始信号后时钟线已经被拉低了
    for(t=0;t<8;t++)
    {              
        IIC_SDA=(txd&0x80);
        txd<<=1;
		SCL_Clr();
		NOP4();		// 实际上延时了1.67us
		SCL_Set();
    }
}

// IIC读一字节
static u8 IIC_Read_Byte(unsigned char ack)
{
	unsigned char i,receive=0;
	SDA_IN();
    for(i=0;i<8;i++ )
	{
        SCL_Set();
		delay_1_us(3);		// 需要延时2us，实际上延时了2.5us
		SCL_Clr();
        receive<<=1;
        if(READ_SDA)receive++;   
		delay_1_us(2);	// 需要延时1us，实际上延时了1.67us
    }					 
    if (!ack)
        IIC_NAck();
    else
        IIC_Ack();
    return receive;
}
