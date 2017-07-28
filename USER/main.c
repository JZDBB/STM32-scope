#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "led.h"
#include "lcd.h"
#include "adc.h"
#include "background.h"


int main(void)
{ 
 	u16 adcx;
	float temp;
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
	Adc_Init();         //初始化ADC
	
	set_background();
	
	POINT_COLOR=RED; 
	
	while(1)
	{ 
		/*adcx=Get_Adc_Average(ADC_Channel_5,20);//获取通道5的转换值，20次取平均
		LCD_ShowxNum(134,130,adcx,4,16,0,WHITE,BLACK);    //显示ADCC采样后的原始值
		temp=(float)adcx*(3.3/4096);          //获取计算后的带小数的实际电压值，比如3.1111
		adcx=temp;                            //赋值整数部分给adcx变量，因为adcx为u16整形
		LCD_ShowxNum(134,150,adcx,1,16,0,WHITE,BLACK);    //显示电压值的整数部分，3.1111的话，这里就是显示3
		temp-=adcx;                           //把已经显示的整数部分去掉，留下小数部分，比如3.1111-3=0.1111
		temp*=1000;                           //小数部分乘以1000，例如：0.1111就转换为111.1，相当于保留三位小数。
		LCD_ShowxNum(150,150,temp,3,16,0X80,WHITE,BLACK); //显示小数部分（前面转换为了整形显示），这里显示的就是111.
		LED0=!LED0;
		delay_ms(250);	*/
	}
}



