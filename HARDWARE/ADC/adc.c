#include "adc.h"
#include "delay.h"		 

#define BUFFE (640)

u16 ADC_BUFF[BUFFE];

void  ADC_DMA_Init()
{
	GPIO_InitTypeDef  GPIO_InitStructure;
	ADC_CommonInitTypeDef ADC_CommonInitStructure;
	ADC_InitTypeDef       ADC_InitStructure;
	DMA_InitTypeDef  DMA_InitStructure;

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);//??GPIOA??
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE); //??ADC1??
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA2,ENABLE);

	RCC_APB2PeriphResetCmd(RCC_APB2Periph_ADC1,ENABLE);	  //ADC1??
	RCC_APB2PeriphResetCmd(RCC_APB2Periph_ADC1,DISABLE);	//????

	DMA_DeInit(DMA2_Stream0);
	while (DMA_GetCmdStatus(DMA2_Stream0) != DISABLE) {} //??DMA???
	/* ?? DMA Stream */
	DMA_InitStructure.DMA_Channel = DMA_Channel_0;  //????
	DMA_InitStructure.DMA_PeripheralBaseAddr = (u32)&ADC1->DR;//DMA????
	DMA_InitStructure.DMA_Memory0BaseAddr = (u32)ADC_BUFF;//DMA ???0??
	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralToMemory;//????????
	DMA_InitStructure.DMA_BufferSize = BUFFE;//?????
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;//???????
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;//???????
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;//??????:16?
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;//???????:16?
	DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;
	DMA_InitStructure.DMA_Priority = DMA_Priority_High;//?????
	DMA_InitStructure.DMA_FIFOMode = DMA_FIFOMode_Disable;
	DMA_InitStructure.DMA_FIFOThreshold = DMA_FIFOThreshold_HalfFull;
	DMA_InitStructure.DMA_MemoryBurst = DMA_MemoryBurst_Single;//?????????
	DMA_InitStructure.DMA_PeripheralBurst = DMA_PeripheralBurst_Single;//????????
	DMA_Init(DMA2_Stream0, &DMA_InitStructure);//???DMA Stream
	DMA_Cmd(DMA2_Stream0,ENABLE);

	//????ADC1??5 IO?
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AN;//????
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL ;//?????
	GPIO_Init(GPIOA, &GPIO_InitStructure);//???

	ADC_CommonInitStructure.ADC_Mode = ADC_Mode_Independent;
	ADC_CommonInitStructure.ADC_TwoSamplingDelay = ADC_TwoSamplingDelay_5Cycles;
	ADC_CommonInitStructure.ADC_DMAAccessMode = ADC_DMAAccessMode_Disabled;
	ADC_CommonInitStructure.ADC_Prescaler = ADC_Prescaler_Div4;//???4??
	ADC_CommonInit(&ADC_CommonInitStructure);//???

	ADC_InitStructure.ADC_Resolution = ADC_Resolution_12b;//12???
	ADC_InitStructure.ADC_ScanConvMode = DISABLE;
	ADC_InitStructure.ADC_ContinuousConvMode = DISABLE;
	ADC_InitStructure.ADC_ExternalTrigConvEdge = ADC_ExternalTrigConvEdge_Rising;//??????,??????
	ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_T3_CC1;
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;//???
	ADC_InitStructure.ADC_NbrOfConversion = 1;
	ADC_Init(ADC1, &ADC_InitStructure);//ADC???


	ADC_RegularChannelConfig(ADC1, ADC_Channel_5, 1, ADC_SampleTime_3Cycles );

	ADC_DMARequestAfterLastTransferCmd(ADC1, ENABLE);
	ADC_DMACmd(ADC1,ENABLE);
	ADC_Cmd(ADC1, ENABLE);//??AD???

	//ADC_SoftwareStartConv(ADC1);
}


void Get_Value(){
	ADC_DMA_Init();
	TIM_Cmd(TIM3, ENABLE);
	while(DMA_GetFlagStatus(DMA2_Stream0,DMA_FLAG_TCIF0)==RESET);
	TIM_Cmd(TIM3, DISABLE);
}													   
