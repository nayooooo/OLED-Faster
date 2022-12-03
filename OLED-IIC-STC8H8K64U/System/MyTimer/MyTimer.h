#ifndef __MYTIMER_H
#define __MYTIMER_H

#include "config.h"
#include "timer.h"

/*---------------- 隐藏使用的定时器 ----------------*/

#define Timer0_Int_Times 1000  // 定时器0的频率

#define My_Timer Timer0
#define My_Timer_Int_Times Timer0_Int_Times

/*---------------- 隐藏使用的定时器 ----------------*/

void MyTimer_Init(void);

#endif