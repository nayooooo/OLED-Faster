#ifndef __MYTIMER_H
#define __MYTIMER_H

#include "config.h"
#include "timer.h"

/*---------------- ����ʹ�õĶ�ʱ�� ----------------*/

#define Timer0_Int_Times 1000  // ��ʱ��0��Ƶ��

#define My_Timer Timer0
#define My_Timer_Int_Times Timer0_Int_Times

/*---------------- ����ʹ�õĶ�ʱ�� ----------------*/

void MyTimer_Init(void);

#endif