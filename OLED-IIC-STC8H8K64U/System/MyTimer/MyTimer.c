#include "MyTimer.h"

#include "screen.h"

u32 timer0_sec = 0;

static void MyTimer0_Init(void)
{
	TIM_InitTypeDef TIM_InitStructure;
	
	TIM_InitStructure.TIM_Mode		= TIM_16BitAutoReload;	// 16位自动重装
	TIM_InitStructure.TIM_Priority	= Priority_1;			// 中断优先级1
	TIM_InitStructure.TIM_Interrupt	= ENABLE;				// 允许中断
	TIM_InitStructure.TIM_ClkSource	= TIM_CLOCK_1T;			// 指定时钟源
	TIM_InitStructure.TIM_ClkOut	= DISABLE;				// 不输出高速脉冲
	TIM_InitStructure.TIM_Value		= 65536UL - (MAIN_Fosc / Timer0_Int_Times);	// 初值
	TIM_InitStructure.TIM_Run		= ENABLE;				// 开始运行
	while(Timer_Inilize(My_Timer, &TIM_InitStructure));
}

void MyTimer_Init(void)
{
	MyTimer0_Init();
}

/********************* Timer0中断函数************************/
extern u8 OLED_Event_Flag;
extern u32 frame;
extern u32 f_OLED;

void timer0_int (void) interrupt TIMER0_VECTOR
{
	static u16 i = 0;
	
	i++;
	if(i>=Timer0_Int_Times)  // 每1秒计算一次频率
	{
		i = 0;
		timer0_sec++;
		if(timer0_sec)
		{
			f_OLED = (u32)(frame / timer0_sec);
			OLED_Event_Flag = OLED_Update_Event;
		}
		else frame = 0;
	}
}









