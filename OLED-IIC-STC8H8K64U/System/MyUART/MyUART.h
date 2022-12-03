#ifndef __MYUSART_H
#define __MYUSART_H

#include "config.h"

#include "UART.h"
#include "GPIO.h"

/* 串口宏 ------------------------------------*/
#define UART1_BaudRate		115200UL
#define My_UART_BaudRate	UART1_BaudRate

#define UART1_Port			GPIO_P3
#define UART1_Rx_Pin		P30
#define UART1_Tx_Pin		P31
#define My_UART_Port		UART1_Port
#define My_UART_Rx_Pin		UART1_Rx_Pin
#define My_UART_Tx_Pin		UART1_Tx_Pin

#define My_COM_TX_Lenth		COM_TX1_Lenth
#define My_COM_RX_Lenth		COM_RX1_Lenth
#define My_UART				UART1

/* 隐藏使用的串口 ----------------------------*/
extern COMx_Define *My_COM;
extern u8 xdata * xdata My_TX_Buffer;
extern u8 xdata * xdata My_RX_Buffer;

/* 串口相关函数 ------------------------------*/
char putchar(char ch);

void My_UART_Init(void);

void My_TX_write2buff(u8 dat);
void My_PrintString(u8 *puts);
void My_UART_Echo(void);

#endif