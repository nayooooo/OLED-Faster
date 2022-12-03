#include "MyUART.h"

#include "delay.h"

/*---------------------------------------
 *
 * ����������������15ms
 *
 --------------------------------------*/

COMx_Define *My_COM = &COM1;
u8 xdata * xdata My_TX_Buffer = TX1_Buffer;
u8 xdata * xdata My_RX_Buffer = RX1_Buffer;

// ��¼���ջ��������յ��ַ���Ŀ
// �ڴ��ڻش�ʱ������
u8 My_RX_Cnt = 0;

/* �ض���fputc -------------------------------------------*/
#include <stdio.h>
char putchar(char ch)
{
	My_TX_write2buff((u8)ch);
	return ch;
}

/* ��ʼ������ --------------------------------------------*/
static void UART_GPIO_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	GPIO_InitStructure.Pin	= UART1_Rx_Pin|UART1_Tx_Pin;	// UART1.Rx UART1.Tx
	GPIO_InitStructure.Mode	= GPIO_PullUp;					// ׼˫���
	GPIO_Inilize(UART1_Port, &GPIO_InitStructure);
}

static void UART1_Init(void)
{
	COMx_InitDefine COMx_InitStructure;
	
	COMx_InitStructure.UART_Mode = UART_8bit_BRTx;			// 8λ���ݣ��ɱ䲨����
	COMx_InitStructure.UART_BRT_Use = BRT_Timer1;			// ʹ�ö�ʱ��1��Ϊ�����ʷ�����
	COMx_InitStructure.UART_BaudRate = UART1_BaudRate;		// ������Ϊ115200
	COMx_InitStructure.Morecommunicate = DISABLE;			// ��ֹ���ͨѶ
	COMx_InitStructure.UART_RxEnable = ENABLE;				// �������
	COMx_InitStructure.BaudRateDouble = DISABLE;			// ��ֹ�����ʼӱ�
	COMx_InitStructure.UART_Interrupt = ENABLE;				// �����жϿ���
	COMx_InitStructure.UART_Priority = Priority_0;			// 0���ȼ�
	COMx_InitStructure.UART_P_SW = UART1_SW_P30_P31;		// ʹ��P30��P31�˿�
	UART_Configuration(UART1, &COMx_InitStructure);
}

void My_UART_Init(void)
{
	UART_GPIO_Config();
	UART1_Init();
	
	printf("\r\nSTC8H8K64U UART1 Test Programme!\r\n");  // UART1�������
}

/* ���ڷ��ͽ��� -------------------------------------------*/
void My_TX_write2buff(u8 dat)
{
	TX1_write2buff(dat);
}

void My_PrintString(u8 *puts)
{
	PrintString1(puts);
}

// ���ڻش�
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

/* �����жϺ��� -------------------------------------------*/
void UART1_int (void) interrupt UART1_VECTOR
{
	if(RI)  // Ӧ�������˵ݹ�
	{
		RI = 0;
		if(COM1.B_RX_OK == 0)
		{
			if(COM1.RX_Cnt >= COM_RX1_Lenth)	COM1.RX_Cnt = 0;
			RX1_Buffer[COM1.RX_Cnt++] = SBUF;  // �����￪ʼ��
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