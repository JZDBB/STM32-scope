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

/*******************************************************************/
//PC0 PC1 PC2 -- A B C
//PC7 gain  
//PC8 AC\DC
//PA5 signal-input
//PB3 square-signal for frequency
/*******************************************************************/


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

void draw()
{
	int k;
	for(k = 0;k<250;k++)
	{
		draw_point(k,arr_plot[k],YELLOW);
		draw_line(k,arr_plot[k],k+1,arr_plot[k+1],YELLOW);
	}
}

void mean()
{
	float min0,max0,min1,max1,k,b;
	int i;
	min0 = arr_plot[0];
	max0 = arr_plot[0];
	for(i = 0;i<250;i++)
	{
		if(min0>arr_plot[i])
		{
			min0 = arr_plot[i];
		}
		if(max0<arr_plot[i])
		{
			max0 = arr_plot[i];
		}
	}
	for(i = 2;i<248;i++)
	{
		arr_plot[i] = (arr_plot[i-2]+arr_plot[i-1]+arr_plot[i]+arr_plot[i+1]+arr_plot[i+2])/5;
	}
	min1 = arr_plot[0];
	max1 = arr_plot[0];
	for(i = 0;i<250;i++)
	{
		if(min1>arr_plot[i])
		{
			min1 = arr_plot[i];
		}
		if(max1<arr_plot[i])
		{
			max1 = arr_plot[i];
		}
	}
	k = (max1-min1)/(max0-min0);
	b = (min1*max0-max1*min0)/(max0-min0);
	for(i = 2;i<248;i++)
	{
		arr_plot[i] = k*arr_plot[i]+b;
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
	delay_ms(500);
	TIM4_Int_Init(1000-1,8400-1);
	TIM_Cnt_Init();
	
	set_background();
	Get_Value();
	vpp = ADC_Get_Vpp();
	
	while(1)
	{ 
		vcc_div = V[magnitude_flag-1];
		if(pause == 0)
		{
			if(scan_flag < 12)
			{
				clear();
				Grid();
				for(j=index2;j<index2+250;j++)
				{
					temp = getvalue(j-index2,det);
					temp1 = getvalue(j-index2+1,det);
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
					/*draw_point(j-index2,arr_plot[j-index2],BLACK);
					draw_line(j-index2,arr_plot[j-index2],j-index2+1,arr_plot[j-index2+1],BLACK);
					draw_point(j-index2,temp,YELLOW);				
					draw_line(j-index2,temp,j-index2+1,temp1,YELLOW);*/
					arr_plot[j-index2] = temp;
				}
				mean();
				draw();
			}
			else
			{
				clear();
				Grid();
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
					draw_point(j-index2,temp,YELLOW);				
					draw_line(j-index2,temp,j-index2+1,temp1,YELLOW);
					arr_plot[j-index2] = temp;
				}
			}
			vol = ADC_BUFF[j] * 3.3f *multiple/ 4095;
			LCD_ShowfloatNum(46,203,vol,6,3,16,BLACK,RED);
			frequency = 1000000;//(u32)TIM_ExtCntFreq;
			LCD_ShowlongNum(222,203,frequency,8,16,BLACK,RED);
			LCD_ShowfloatNum(62,220,vpp,6,3,16,BLACK,RED);
			Get_Value();
			vpp = ADC_Get_Vpp();
			delay_ms(500);
		}
		else
		{
			if(update)
			{
				if(scan_flag < 12)
				{
					clear();
					Grid();
					for(j=index2+hor;j<index2+250+hor;j++)
					{
						temp = getvalue(j-index2,det) + ver;
						temp1 = getvalue(j-index2+1,det) + ver;
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
						/*draw_point(j-index2,arr_plot[j-index2],BLACK);
						draw_line(j-index2,arr_plot[j-index2],j-index2+1,arr_plot[j-index2+1],BLACK);
						draw_point(j-index2,temp,YELLOW);				
						draw_line(j-index2,temp,j-index2+1,temp1,YELLOW);*/
						arr_plot[j-index2-hor] = temp;
					}
					mean();
					draw();
				}
				else
				{
					clear();
					Grid();
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
				}
				delay_ms(100);
				update = 0;
			}	
		}
	}
}

