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
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//����ϵͳ�ж����ȼ�����2
	delay_init(168);    //��ʼ����ʱ����
	uart_init(115200);	//��ʼ�����ڲ�����Ϊ115200
	LED_Init();					//��ʼ��LED 
 	LCD_Init();         //��ʼ��LCD�ӿ�
	LCD_Scan_Dir(D2U_L2R);
	LCD_Clear(BLACK);
	ADC_DMA_Init();      //��ʼ��ADC
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



