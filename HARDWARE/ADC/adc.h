#ifndef __ADC_H
#define __ADC_H	
#include "sys.h" 
#include "stm32f4xx.h"

#define BUFFE (640)

extern u16 ADC_BUFF[BUFFE];
 							   
void  ADC_DMA_Init();
void Get_Value();

#endif 















