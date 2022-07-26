#include "MyTimer.h"

#include "timer.h"

#include "screen.h"

extern u8 OLED_Event_Flag;
extern u32 frame;
extern u32 f_OLED;

static void MyTimer0_Init(void)
{
	TIM_InitTypeDef TIM_InitStructure;
	
	TIM_InitStructure.TIM_Mode		= TIM_16BitAutoReload;	// 16λ�Զ���װ
	TIM_InitStructure.TIM_Priority	= Priority_1;			// �ж����ȼ�1
	TIM_InitStructure.TIM_Interrupt	= ENABLE;				// �����ж�
	TIM_InitStructure.TIM_ClkSource	= TIM_CLOCK_1T;			// ָ��ʱ��Դ
	TIM_InitStructure.TIM_ClkOut	= DISABLE;				// �������������
	TIM_InitStructure.TIM_Value		= 65536UL - (MAIN_Fosc / My_Timer_Int_Times);	// ��ֵ
	TIM_InitStructure.TIM_Run		= ENABLE;				// ��ʼ����
	while(Timer_Inilize(My_Timer, &TIM_InitStructure));
}

void MyTimer_Init(void)
{
	MyTimer0_Init();
}

/********************* Timer0�жϺ���************************/
void timer0_int (void) interrupt TIMER0_VECTOR
{
	static u16 i = 0;
	static u32 sec = 0;
	
	i++;
	if(i>=My_Timer_Int_Times)  // ÿ1�����һ��Ƶ��
	{
		i = 0;
		sec++;
		if(sec)
		{
			f_OLED = (u32)(frame/sec);
			OLED_Event_Flag = OLED_Update_F;
		}
		else frame = 0;
	}
}