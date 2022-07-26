#ifndef __SCREEN_H
#define __SCREEN_H

#include "config.h"
#include "oled.h"

typedef enum{
	OLED_No_Event,			// 无事件
	OLED_Update_F			// 更新频率
}OLED_Event_Flag_Typedef;

void OLED_Mes_Type(void);

#endif
