#ifndef _TIMER_H
#define _TIMER_H
#include "sys.h"
#include "stm32f4xx.h"

extern long long count;
extern u32 frequency;
extern float TIM_ExtCntFreq;

void choose(u16 color);
void TIM3_Init(void);
void TIM4_Int_Init(u16 arr,u16 psc);
void TIM_Cnt_Init(void);

#endif
