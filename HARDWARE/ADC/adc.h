#ifndef __ADC_H
#define __ADC_H	
#include "sys.h" 
#include "stm32f4xx.h"

#define BUFFE (6000)

extern u16 ADC_BUFF[BUFFE];
extern u16 index2;
extern u16 index1;
extern float multiple;
extern int mode_hard;
extern u32 max_data;
extern u32 min_data;
extern float det;
extern float high_freq_period;
 							   
void  ADC_DMA_Init(void);
void Get_Value(void);
float ADC_Get_Vpp(void);
float getvalue(u16 index, float det_T);

#endif 















