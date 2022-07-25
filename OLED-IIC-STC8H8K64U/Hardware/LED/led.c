#include "led.h"
#include "GPIO.h"

void LED_GPIO_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	GPIO_InitStructure.Mode = GPIO_OUT_PP;	// 普通推挽输出
	GPIO_InitStructure.Pin = LED_0_Pin|LED_1_Pin;  // P4.5 P4.6
	GPIO_Inilize(LED_GPIO_Port, &GPIO_InitStructure);
	
	// 熄灭所有LED
	LED(0) = LED_OFF; LED(1) = LED_OFF;
}