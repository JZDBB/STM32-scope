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
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//����ϵͳ�ж����ȼ�����2
	delay_init(168);    //��ʼ����ʱ����
	uart_init(115200);	//��ʼ�����ڲ�����Ϊ115200
	LED_Init();					//��ʼ��LED 
 	LCD_Init();         //��ʼ��LCD�ӿ�
	LCD_Scan_Dir(D2U_L2R);
	LCD_Clear(BLACK);
	Adc_Init();         //��ʼ��ADC
	
	set_background();
	
	POINT_COLOR=RED; 
	
	while(1)
	{ 
		/*adcx=Get_Adc_Average(ADC_Channel_5,20);//��ȡͨ��5��ת��ֵ��20��ȡƽ��
		LCD_ShowxNum(134,130,adcx,4,16,0,WHITE,BLACK);    //��ʾADCC�������ԭʼֵ
		temp=(float)adcx*(3.3/4096);          //��ȡ�����Ĵ�С����ʵ�ʵ�ѹֵ������3.1111
		adcx=temp;                            //��ֵ�������ָ�adcx��������ΪadcxΪu16����
		LCD_ShowxNum(134,150,adcx,1,16,0,WHITE,BLACK);    //��ʾ��ѹֵ���������֣�3.1111�Ļ������������ʾ3
		temp-=adcx;                           //���Ѿ���ʾ����������ȥ��������С�����֣�����3.1111-3=0.1111
		temp*=1000;                           //С�����ֳ���1000�����磺0.1111��ת��Ϊ111.1���൱�ڱ�����λС����
		LCD_ShowxNum(150,150,temp,3,16,0X80,WHITE,BLACK); //��ʾС�����֣�ǰ��ת��Ϊ��������ʾ����������ʾ�ľ���111.
		LED0=!LED0;
		delay_ms(250);	*/
	}
}



