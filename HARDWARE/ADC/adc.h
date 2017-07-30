#ifndef __ADC_H
#define __ADC_H	
#include "sys.h" 
#include "stm32f4xx.h"

#define BUFFE (640)

extern u16 ADC_BUFF[BUFFE];
extern u16 index2;
extern u16 index1;
extern u8 flag_change;
extern u8 flag_50us;
extern int inter_b;
extern float multiple;
extern int mode_hard;
extern u32 max_data;
extern u32 min_data;
 							   
void  ADC_DMA_Init();
void Get_Value();
u16 ADC_Get_Vpp(void);

#endif 















