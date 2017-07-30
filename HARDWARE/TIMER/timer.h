#ifndef _TIMER_H
#define _TIMER_H
#include "sys.h"
#include "stm32f4xx.h"

void choose(u16 color);
void TIM3_Init();
void TIM2_Int_Init(u16 arr,u16 psc);

#endif
