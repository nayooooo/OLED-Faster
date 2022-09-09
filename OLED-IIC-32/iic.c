#include "iic.h"

#include "stm32f10x_rcc.h"
#include "stm32f10x_gpio.h"

#include "delay.h"
#include "oled.h"
/**********************************************
//		GND -> GND
//		VCC -> VCC
//		SCL -> GPIOB6
//		SDA -> GPIOB7
**********************************************/
 
//初始化GPIO
void IIC_GPIO_Init(void)
{					     
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(	RCC_APB2Periph_GPIOB, ENABLE );
	   
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6|GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP ;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	GPIO_SetBits(GPIOB,GPIO_Pin_6|GPIO_Pin_7);
}

/* IIC读写函数 -------------------------------------*/
/* 慢速读写 ----------------------------------------*/
void IIC_WR_Byte(u8 dat, u8 cmd)
{
	IIC_Start();
	IIC_Send_Byte(SLAVE_ADDRESS);
	IIC_Wait_Ack();	
	if(cmd)		// 数据
	{
		IIC_Send_Byte(OLED_DATA_CHR);
	}
	else		// 命令
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
	IIC_Send_Byte(SLAVE_ADDRESS);
	IIC_Wait_Ack();	
	IIC_Send_Byte(OLED_DATA_CHR);
	IIC_Wait_Ack();
	IIC_Send_Byte(dat); 
	IIC_Wait_Ack();	
	IIC_Stop();
}

void IIC_WR_Byte_Cmd(u8 dat)
{
	IIC_Start();
	IIC_Send_Byte(SLAVE_ADDRESS);
	IIC_Wait_Ack();
	IIC_Send_Byte(OLED_CMD_CHR);
	IIC_Wait_Ack();
	IIC_Send_Byte(dat); 
	IIC_Wait_Ack();	
	IIC_Stop();
}

/* 快速读写 ----------------------------------------*/
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

void IIC_WR_Byte_Dat_Fast(u8 *buf, u16 size)
{
	IIC_Start();
	IIC_Send_Byte(SLAVE_ADDRESS);            // Slave address
	IIC_Wait_Ack();
	IIC_Send_Byte(OLED_DATA_CHR);
	IIC_Wait_Ack();
	while(size--){
		IIC_Send_Byte(*buf);
		IIC_Wait_Ack();
		buf++;
	}
	IIC_Stop();
}

void IIC_WR_Byte_Cmd_Fast(u8 *buf, u16 size)
{
	IIC_Start();
	IIC_Send_Byte(SLAVE_ADDRESS);            // Slave address
	IIC_Wait_Ack();
	IIC_Send_Byte(OLED_CMD_CHR);
	IIC_Wait_Ack();
	while(size--){
		IIC_Send_Byte(*buf);
		IIC_Wait_Ack();
		buf++;
	}
	IIC_Stop();
}

/* IIC协议模块 -------------------------------------*/
static void IIC_Start(void)
{
	SDA_OUT();
	IIC_SDA=1;	  	  
	IIC_SCL=1;
	delay_us(4);
 	IIC_SDA=0;
	delay_us(4);
	IIC_SCL=0;
}

static void IIC_Stop(void)
{
	SDA_OUT();
	IIC_SCL=0;
	IIC_SDA=0;
 	delay_us(4);
	IIC_SCL=1; 
	IIC_SDA=1;
	delay_us(4);							   	
}

static u8 IIC_Wait_Ack(void)
{
	u8 ucErrTime=0;
	SDA_IN();
	IIC_SDA=1;delay_us(1);	   
	IIC_SCL=1;delay_us(1);	 
	while(READ_SDA)
	{
		ucErrTime++;
		if(ucErrTime>250)
		{
			IIC_Stop();
			return 1;
		}
	}
	IIC_SCL=0;
	return 0;  
}

static void IIC_Ack(void)
{
	IIC_SCL=0;
	SDA_OUT();
	IIC_SDA=0;
	delay_us(2);
	IIC_SCL=1;
	delay_us(2);
	IIC_SCL=0;
}

static void IIC_NAck(void)
{
	IIC_SCL=0;
	SDA_OUT();
	IIC_SDA=1;
	delay_us(2);
	IIC_SCL=1;
	delay_us(2);
	IIC_SCL=0;
}

static void IIC_Send_Byte(u8 txd)
{                        
    u8 t;   
	SDA_OUT(); 	    
    IIC_SCL=0;
    for(t=0;t<8;t++)
    {              
        IIC_SDA=(txd&0x80)>>7;
        txd<<=1; 	  
		delay_us(2);
		IIC_SCL=1;
		delay_us(2); 
		IIC_SCL=0;	
		delay_us(2);
    }	 
}

static u8 IIC_Read_Byte(unsigned char ack)
{
	unsigned char i,receive=0;
	SDA_IN();
    for(i=0;i<8;i++ )
	{
        IIC_SCL=0; 
        delay_us(2);
		IIC_SCL=1;
        receive<<=1;
        if(READ_SDA)receive++;   
		delay_us(1); 
    }					 
    if (!ack)
        IIC_NAck();
    else
        IIC_Ack();
    return receive;
}
