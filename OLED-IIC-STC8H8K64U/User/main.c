#include "config.h"
#include "delay.h"

#include "led.h"
#include "oled.h"
#include "screen.h"

void main()
{
	u32 i = 0;
	
	LED_GPIO_Config();
	OLED_Init();
	
	while(1)
	{
		i++;
		OLED_Test(i);
		OLED_Refresh_Gram();
	}
}