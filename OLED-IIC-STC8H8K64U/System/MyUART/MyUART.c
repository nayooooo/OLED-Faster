#include "MyUART.h"

#include "delay.h"

/*---------------------------------------
 *
 * 发送数据请间隔至少15ms
 *
 --------------------------------------*/

COMx_Define *My_COM = &COM1;
u8 xdata * xdata My_TX_Buffer = TX1_Buffer;
u8 xdata * xdata My_RX_Buffer = RX1_Buffer;

// 记录接收缓冲区接收的字符数目
// 在串口回传时被更新
u8 My_RX_Cnt = 0;

/* 重定向fputc -------------------------------------------*/
#include <stdio.h>
char putchar(char ch)
{
	My_TX_write2buff((u8)ch);
	return ch;
}

/* 初始化函数 --------------------------------------------*/
static void UART_GPIO_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	GPIO_InitStructure.Pin	= UART1_Rx_Pin|UART1_Tx_Pin;	// UART1.Rx UART1.Tx
	GPIO_InitStructure.Mode	= GPIO_PullUp;					// 准双向口
	GPIO_Inilize(UART1_Port, &GPIO_InitStructure);
}

static void UART1_Init(void)
{
	COMx_InitDefine COMx_InitStructure;
	
	COMx_InitStructure.UART_Mode = UART_8bit_BRTx;			// 8位数据，可变波特率
	COMx_InitStructure.UART_BRT_Use = BRT_Timer1;			// 使用定时器1作为波特率发生器
	COMx_InitStructure.UART_BaudRate = UART1_BaudRate;		// 波特率为115200
	COMx_InitStructure.Morecommunicate = DISABLE;			// 禁止多机通讯
	COMx_InitStructure.UART_RxEnable = ENABLE;				// 允许接收
	COMx_InitStructure.BaudRateDouble = DISABLE;			// 禁止波特率加倍
	COMx_InitStructure.UART_Interrupt = ENABLE;				// 允许中断控制
	COMx_InitStructure.UART_Priority = Priority_0;			// 0优先级
	COMx_InitStructure.UART_P_SW = UART1_SW_P30_P31;		// 使用P30、P31端口
	UART_Configuration(UART1, &COMx_InitStructure);
}

void My_UART_Init(void)
{
	UART_GPIO_Config();
	UART1_Init();
	
	printf("\r\nSTC8H8K64U UART1 Test Programme!\r\n");  // UART1配置完成
}

/* 串口发送接收 -------------------------------------------*/
void My_TX_write2buff(u8 dat)
{
	TX1_write2buff(dat);
}

void My_PrintString(u8 *puts)
{
	PrintString1(puts);
}

// 串口回传
void My_UART_Echo(void)
{
	u8 i;
	
	if(My_COM->RX_TimeOut > 0)
	{
		if(--My_COM->RX_TimeOut == 0)
		{
			if(My_COM->RX_Cnt > 0)
			{
				My_RX_Cnt = My_COM->RX_Cnt;
				for(i=0; i<My_COM->RX_Cnt; i++) My_TX_write2buff(My_RX_Buffer[i]);
				My_COM->RX_Cnt = 0;
			}
		}
	}
}

/* 串口中断函数 -------------------------------------------*/
void UART1_int (void) interrupt UART1_VECTOR
{
	if(RI)  // 应该是用了递归
	{
		RI = 0;
		if(COM1.B_RX_OK == 0)
		{
			if(COM1.RX_Cnt >= COM_RX1_Lenth)	COM1.RX_Cnt = 0;
			RX1_Buffer[COM1.RX_Cnt++] = SBUF;  // 从这里开始递
			COM1.RX_TimeOut = TimeOutSet1;
		}
	}

	if(TI)
	{
		TI = 0;
		if(COM1.TX_read != COM1.TX_write)
		{
		 	SBUF = TX1_Buffer[COM1.TX_read];
			if(++COM1.TX_read >= COM_TX1_Lenth)		COM1.TX_read = 0;
		}
		else	COM1.B_TX_busy = 0;
	}
}