#include "screen.h"

#include <stdlib.h>
#include <math.h>

#include "delay.h"

u8 OLED_Event_Flag = OLED_No_Event;

u32 frame = 0;
u32 f_OLED;  // OLEDµÄÆµÂÊ

void OLED_Mes_Type(void)
{
	OLED_ShowString(0, 0, (u8*)"frame:", 16, FILL);
	OLED_ShowString(0, 16, (u8*)"f:0  Hz", 16, FILL);
}