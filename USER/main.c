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
 	u16 adcx;
	int i;
	u8 vpp_buf[7];
	u8 v_buf[7];
	u8 duty_buf[8];
	u8 vol;
	u16 duty = 0;
	
	
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
	
	set_background();
	Get_Value();
	
	while(1)
	{ 
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
				draw_point(j-index2,arr_plot[i+1],BLACK);
				draw_point(j-index2,temp,YELLOW);				
				draw_line(j-index2,temp,j-index2+1,temp1,YELLOW);
				Grid();
				arr_plot[i] = temp;
				i++;
				vol = ADC_BUFF[j] * 3300 *multiple/ 4095;
				LCD_ShowxNum(46,203,vol,6,16,0,BLACK,RED);
				delay_ms(50);
				//LCD_ShowxNum(262,102,arr_freq,RED,BLACK);
			}
			Get_Value();
		}
		else
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
				draw_point(j-index2,temp,YELLOW);				
				draw_line(j-index2,temp,j-index2+1,temp1,YELLOW);
				arr_plot[i] = temp;
				i++;
			}
			Grid();
		}
	}
}
