#include "adc.h"
#include "delay.h"
#include "background.h"
#include "timer.h"

#define BUFFE (6000)

u16 ADC_BUFF[BUFFE];
u16 index2 = 160;
u16 index1 = 0;
float multiple = 1;
int mode_hard = 0;
u32 max_data = 0;
u32 min_data = 0;
float det = 0;
float freq = 0;
float high_freq_period = 200;

void  ADC_DMA_Init(void)
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


	ADC_RegularChannelConfig(ADC1, ADC_Channel_5, 1, ADC_SampleTime_3Cycles);

	ADC_DMARequestAfterLastTransferCmd(ADC1, ENABLE);
	ADC_DMACmd(ADC1,ENABLE);
	ADC_Cmd(ADC1, ENABLE);//??AD???

	//ADC_SoftwareStartConv(ADC1);
}


void Get_Value(void)
{
	ADC_DMA_Init();
	TIM_SetCounter(TIM3,0);	
	if(scan_flag>11)
	{	
		TIM_PrescalerConfig(TIM3,41,TIM_PSCReloadMode_Immediate);
		TIM_SetAutoreload(TIM3, (F[scan_flag-1]/25)*2-1); //设定扫描速度
	}
	else
	{
		TIM_PrescalerConfig(TIM3,0,TIM_PSCReloadMode_Immediate);
		high_freq_period = 200;
		det = 0;
		freq = frequency;
		freq /= 1000000;
		while(det*freq>0.05f||det*freq<0.03f)
		{
			high_freq_period++;
			det = high_freq_period/84.0f;
			while(det>0)
			{
				det -=1.0f/freq;
			}
			det += 1.0f/freq;
		}
		TIM_SetAutoreload(TIM3, high_freq_period-1); //设定扫描速度
	}
	TIM_Cmd(TIM3, ENABLE);
	while(DMA_GetFlagStatus(DMA2_Stream0,DMA_FLAG_TCIF0)==RESET);
	TIM_Cmd(TIM3, DISABLE);
}

float ADC_Get_Vpp(void)	   
{
	u32 n=0;
	float pp=0;
	max_data=ADC_BUFF[0];
	min_data=ADC_BUFF[0];
	for(n = 30;n<320;n++)
	{
		if(ADC_BUFF[n]>max_data)
		{
			max_data = ADC_BUFF[n];
		}
		if(ADC_BUFF[n]<min_data)
		{
			min_data = ADC_BUFF[n];
			index2 = n;
		}
	} 	
	pp = (float)(max_data-min_data);
	pp = (float)pp*(3.3f* multiple /4095);
	return pp;
}

float getvalue(u16 index, float det_T)
{
	float index0;
	int i;
	float value = 0;
	float value1 = 0;
	float value2 = 0;
	index0 = index;
	index0 = (float)index0*F[scan_flag-1]/25/det_T;
	i = (int)index0;
	value1 = ADC_BUFF[i] * 3300 * multiple / 4096  *  25 /vcc_div;
	value2 = ADC_BUFF[i + 1] * 3300* multiple / 4096 * 25 / vcc_div;
	value = (float)(index0-(int)index0)*value1+(1-(index0-(int)index0))*value2;
	return value;
}


