#ifndef __SCREEN_H
#define __SCREEN_H

#include "config.h"
#include "oled.h"

typedef enum{
	OLED_No_Event,			// ���¼�
	OLED_Update_F			// ����Ƶ��
}OLED_Event_Flag_Typedef;

void OLED_Mes_Type(void);

#endif
