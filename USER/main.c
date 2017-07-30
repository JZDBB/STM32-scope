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




int main(void)
{ 
 	u16 adcx;
	float temp;
	int i;
	u8 vpp_buf[7];
	u8 v_buf[7];
	u8 duty_buf[8];
	u16 vol;
	u16 duty = 0;
	v_buf[2] = 46;
	vpp_buf[2] = 46;
	duty_buf[6] = 37;
	duty_buf[0] = 32;
	duty_buf[3] = 46;
	duty_buf[7] = '\0';
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//设置系统中断优先级分组2
	delay_init(168);    //初始化延时函数
	uart_init(115200);	//初始化串口波特率为115200
	LED_Init();					//初始化LED 
 	LCD_Init();         //初始化LCD接口
	LCD_Scan_Dir(D2U_L2R);
	LCD_Clear(BLACK);
	ADC_DMA_Init();      //初始化ADC
	TIM3_Init();
	set_background();
	
	while(1)
	{ 
		Get_Value();
		
		for(i = 0;i++;i<200)
		{
			temp = ADC_BUFF[i] * 3300 / 4096  *  25 / 50;
			LCD_Fast_DrawPoint(i,temp, YELLOW);
		}
	}
}



