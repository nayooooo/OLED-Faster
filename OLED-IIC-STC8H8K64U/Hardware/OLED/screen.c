#include "screen.h"

#include <stdlib.h>
#include <math.h>

#include "delay.h"

void OLED_Test(u32 nums)
{
	OLED_ShowNums(0, 0, nums, 16, FILL);
}