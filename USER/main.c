#include "stm32f4xx.h"
#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "led.h"
#include "lcd.h"
#include "adc.h"
#include "dma.h"
#include "background.h"
#include "timer.h"
#include "touch.h"

u16 j = 0;
float temp;
float temp1;
extern u8  TIM5CH1_CAPTURE_STA;	//输入捕获状态		    				
extern u32	TIM5CH1_CAPTURE_VAL;	//输入捕获值(TIM2/TIM5是32位)

void clear()
{
	int k;
	for(k = 0;k<250;k++)
	{
		draw_point(k,arr_plot[k],BLACK);
		draw_line(k,arr_plot[k],k+1,arr_plot[k+1],BLACK);
	}
}

int main(void)
{ 
	float vol;
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//设置系统中断优先级分组2
	delay_init(168);    //初始化延时函数
	uart_init(115200);	//初始化串口波特率为115200
	LED_Init();					//初始化LED 
 	LCD_Init();         //初始化LCD接口
	LCD_Scan_Dir(D2U_L2R);
	LCD_Clear(BLACK);
	ADC_DMA_Init();      //初始化ADC
	TIM3_Init();
	Touch_Init();
	TIM2_Int_Init(1000-1,8400-1);
	TIM5_CH1_Cap_Init(0XFFFFFFFF,84-1); //以1Mhz的频率计数
	
	set_background();
	Get_Value();
	vpp = ADC_Get_Vpp();
	
	while(1)
	{ 
		vcc_div = V[magnitude_flag-1];
		if(pause == 0)
		{
			for(j=index2;j<index2+250;j++)
			{
				temp = ADC_BUFF[j] * 3300 * multiple / 4096  *  25 /vcc_div;
				temp1 = ADC_BUFF[j + 1] * 3300* multiple / 4096 * 25 / vcc_div;
				if(temp>200)
				{
					temp=200;
				}
				if(temp<0)
				{
					temp=0;	
				}
				if(temp1>200)
				{
					temp1=200;	
				}
				if(temp1<0)
				{
					temp1=0;	
				}
				draw_point(j-index2,arr_plot[j-index2],BLACK);
				draw_line(j-index2,arr_plot[j-index2],j-index2+1,arr_plot[j-index2+1],BLACK);
				draw_point(j-index2,temp,YELLOW);				
				draw_line(j-index2,temp,j-index2+1,temp1,YELLOW);
				Grid();
				arr_plot[j-index2] = temp;
				vol = ADC_BUFF[j] * 3.3f *multiple/ 4095;
				LCD_ShowfloatNum(46,203,vol,6,3,16,BLACK,RED);
				LCD_ShowxNum(222,203,frequency,8,16,128,BLACK,RED);
				//LCD_ShowlongNum(222,203,frequency,8,16,BLACK,RED);
			}
			LCD_ShowfloatNum(62,220,vpp,6,3,16,BLACK,RED);
			//LCD_ShowxNum(62,220,vpp,6,16,128,BLACK,RED);
			Get_Value();
			vpp = ADC_Get_Vpp();
		}
		else
		{
			if(update)
			{
				clear();
				for(j=index2+hor;j<index2+hor+250;j++)
				{
					temp = ADC_BUFF[j] * 3300 * multiple / 4096  *  25 /vcc_div + ver;
					temp1 = ADC_BUFF[j + 1] * 3300* multiple / 4096 * 25 / vcc_div + ver;
					if(temp>200)
					{
						temp=200;
					}
					if(temp<0)
					{
						temp=0;	
					}
					if(temp1>200)
					{
						temp1=200;	
					}
					if(temp1<0)
					{
						temp1=0;	
					}
					draw_point(j-index2-hor,temp,YELLOW);				
					draw_line(j-index2-hor,temp,j-index2-hor+1,temp1,YELLOW);
					arr_plot[j-index2-hor] = temp;
				}
				Grid();
				delay_ms(100);
				update = 0;
			}
		}
	}
}

