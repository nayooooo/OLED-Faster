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
#ifdef FAST_IIC_FOR_SSD1306
	#define SYSTEM_CORE_CLOCK (72000000)
	uint8_t	fac_hus=SYSTEM_CORE_CLOCK/1000000/2;  // 半us
	uint8_t	fac_125ns=SYSTEM_CORE_CLOCK/1000000/8;  // 125ns
	static void IIC_Fast_Delay_Hus(uint8_t Half_Us)
	{
		u32 ticks;
		u32 told,tnow,tcnt=0;
		u32 reload=SysTick->LOAD;				//LOAD的值	    	 
		ticks=Half_Us*fac_hus; 						//需要的节拍数 
		told=SysTick->VAL;        				//刚进入时的计数器值
		while(1)
		{
			tnow=SysTick->VAL;	
			if(tnow!=told)
			{	    
				if(tnow<told)tcnt+=told-tnow;	//这里注意一下SYSTICK是一个递减的计数器就可以了.
				else tcnt+=reload-tnow+told;	    
				told=tnow;
				if(tcnt>=ticks)break;			//时间超过/等于要延迟的时间,则退出.
			}  
		};
	}
	static void IIC_Fast_Delay_125ns(uint8_t _125_Ns)
	{
		u32 ticks;
		u32 told,tnow,tcnt=0;
		u32 reload=SysTick->LOAD;				//LOAD的值	    	 
		ticks=_125_Ns*fac_125ns; 				//需要的节拍数 
		told=SysTick->VAL;        				//刚进入时的计数器值
		while(1)
		{
			tnow=SysTick->VAL;	
			if(tnow!=told)
			{	    
				if(tnow<told)tcnt+=told-tnow;	//这里注意一下SYSTICK是一个递减的计数器就可以了.
				else tcnt+=reload-tnow+told;	    
				told=tnow;
				if(tcnt>=ticks)break;			//时间超过/等于要延迟的时间,则退出.
			}  
		};
	}
#endif /* FAST_IIC_FOR_SSD1306 */

static void IIC_Start(void)
{
	SDA_OUT();
	SDA_Clr();
	SCL_Clr();
	#ifdef FAST_IIC_FOR_SSD1306
		NOP(1);
	#else
		delay_us(1);
	#endif
 	SDA_Set();
	#ifdef FAST_IIC_FOR_SSD1306
		NOP(1);
	#else
		delay_us(1);
	#endif
	SCL_Set();
}

static void IIC_Stop(void)
{
	SDA_OUT();
	SCL_Set();
	SDA_Set();
	#ifdef FAST_IIC_FOR_SSD1306
		NOP(1);
	#else
		delay_us(1);
	#endif
	SCL_Clr();
	SDA_Clr();
	#ifdef FAST_IIC_FOR_SSD1306
		NOP(1);
	#else
		delay_us(1);
	#endif						   	
}

static u8 IIC_Wait_Ack(void)
{
	u8 ucErrTime=0;
	SDA_IN();SDA_Clr();
	SCL_Clr();
	#ifdef FAST_IIC_FOR_SSD1306
		NOP(1);
	#else
		delay_us(1);
	#endif
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

static void IIC_Send_Byte(u8 txd)
{                        
    u8 t;   
	SDA_OUT(); 	    
    SCL_Set();
    for(t=0;t<8;t++)
    {              
        (txd&0x80) ? (SDA_Clr()) : (SDA_Set());
        txd<<=1;
		#ifdef FAST_IIC_FOR_SSD1306
			NOP(1);
		#else
			delay_us(1);
		#endif
		SCL_Clr();
		#ifdef FAST_IIC_FOR_SSD1306
			NOP(6);
		#else
			delay_us(1);
		#endif
		SCL_Set();	
    }	 
}
