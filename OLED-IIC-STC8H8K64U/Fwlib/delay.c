#include	"delay.h"

void Delay15us(void)		//@24.000MHz
{
	unsigned char i;

	i = 78;
	while (--i);
}

/*------------- 自适应延时函数 -------------*/

// @24.00MHz下
// us=1->1.458us
// us=2->2.708us
void delay_1_us(u16 us)
{
	u16 i;
	do{
		i = MAIN_Fosc / 10000000;
		while(--i);
	}while(--us);
}

void delay_5_us(u16 _5us)
{
	u16 i;
	do{
		i = MAIN_Fosc / 2000000;
		while(--i);
	}while(--_5us);
}

void delay_10_us(u16 _10us)
{
	u16 i;
	do{
		i = MAIN_Fosc / 1000000;
		while(--i);
	}while(--_10us);
}

void delay_ms(u16 ms)
{
	u16 i;
	do{
		i = MAIN_Fosc / 10000;
		while(--i);
	}while(--ms);
}

/*------------- 自适应延时函数 -------------*/