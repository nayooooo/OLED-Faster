#include "config.h"
#include "delay.h"

#include "led.h"
#include "screen.h"
#include "MyTimer.h"

extern u8 OLED_Event_Flag;
extern u32 frame;
extern u32 f_OLED;

void main()
{
	LED_GPIO_Config();
	OLED_Init();
	MyTimer_Init();
	
	OLED_Mes_Type(); OLED_Refresh_Gram();
	
	EA = 1;  // ¿ªÆô×ÜÖÐ¶Ï
	
	while(1)
	{
		frame++;
		
		if(OLED_Event_Flag==OLED_Update_F)
		{
			OLED_ShowNums(16, 16, f_OLED, 16, FILL);
			OLED_Event_Flag = OLED_No_Event;
		}
		
		if(OLED_Event_Flag==OLED_No_Event)
			OLED_ShowNums(48, 0, frame, 16, FILL);
		
		OLED_Refresh_Gram();
	}
}