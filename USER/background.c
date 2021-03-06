#include "background.h"
#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "led.h"
#include "lcd.h"
#include "adc.h"

float vpp;
int flag_move = 0;
int gain = 1;
u8 C_dc_ac = 0;
u8 change_gain = 0;
float arr_plot[250];
u8 pause = 0;
int ver = 0;
int hor = 0;
u16 vcc_div = 1000;
float gao_pin_palus = 0;
int selected = 0;
u8 magnitude_flag =3;
long int scan_flag = 14;
int update = 0;
int n = 0;
int flag_inc = 0;
int flag_dec = 0;
int flag_load = 0;
int flag_mov = 0;
int flag_acdc = 0;
int flag_gain = 0;

float F[21] = {0.01,0.02,0.05,0.1,0.2,0.5,1,2,5,10,20,50,100,200,500,1000,2000,5000,10000,20000,50000};
u16 V[7] = {100,200,500,1000,2000,5000,10000};
u8 arr_F[21][8] = {" 10ns\0"," 20ns\0"," 50ns\0","100ns\0","200ns\0","500ns\0","  1us\0","  2us\0","  5us\0"," 10us\0"," 20us\0"," 50us\0","100us\0","200us\0","500us\0","  1ms\0","  2ms\0","  5ms\0"," 10ms\0"," 20ms\0"," 50ms\0"};
u8 arr_V[7][8] = {"100mV\0","200mV\0","500mV\0","   1V\0","   2V\0","   5V\0","  10V\0"};
u8 arr_gain[8][6] = {"0 0 0\0","0 0 1\0","0 1 0\0","0 1 1\0","1 0 0\0","1 0 1\0","1 1 0\0","1 1 1\0"};
u8 arr_C[2][10] = {"AC\0", "DC\0"};
u8 arr_move[2][9] ={"mov_hor\0","mov_ver\0"};
u8 arr_JDQ[2][3] = {" 0\0"," 1\0"};
float gain_num[8] = {0.05, 0.1, 0.2, 0.4, 8, 10, 20, 25};
float gain_multiple0[8] = {0.036,0.063,0.12,0.226,0.49,0.57,1.13,3};
float gain_multiple1[8] = {0.264,0.54,1.05,2.2,4.2,5.2,9.85,24};
u8 show_gain0[8][8] = {"0.025\0","0.05 \0","0.1  \0","0.2  \0","0.4  \0","0.5  \0","1    \0","2.5  \0"};
u8 show_gain1[8][8] = {"0.25 \0","0.5  \0","1    \0","2    \0","4    \0","5    \0","10   \0","25   \0"};


void set_background(void)
{
	POINT_COLOR = BLUE;
	
	LCD_DrawRectangle(0,0,250,200,POINT_COLOR);
	LCD_DrawLine(0,100,250,100,POINT_COLOR);
	LCD_DrawLine(125,0,125,200,POINT_COLOR);

	POINT_COLOR=RED;
	LCD_DrawRectangle(0,202,320,240,RED);
	LCD_ShowString(5,203,200,16,16,"V(V):",BLACK,POINT_COLOR);
	LCD_ShowString(5,220,200,16,16,"Vpp(V):",BLACK,POINT_COLOR);
	LCD_ShowString(150,203,200,16,16,"Freq(Hz):",BLACK,POINT_COLOR);
	LCD_ShowString(150,220,200,16,16,"duty(%):",BLACK,POINT_COLOR);

	POINT_COLOR=WHITE;
	LCD_DrawRectangle(252,0,320,200,WHITE);
	LCD_DrawRectangle(255,2,316,38,BLUE);
	LCD_DrawRectangle(255,42,316,78,BLUE);
	LCD_DrawRectangle(255,82,316,101,BLUE);
	LCD_DrawRectangle(255,105,316,124,BLUE);
	LCD_DrawRectangle(255,128,283,147,BLUE);
	LCD_DrawRectangle(288,128,316,147,BLUE);
	LCD_DrawRectangle(255,151,316,170,BLUE);
	LCD_DrawRectangle(255,2,316,38,WHITE);
	POINT_COLOR=BLUE;
	LCD_ShowString(258,3,200,16,16,"VOL/div",BLACK,POINT_COLOR);	
	LCD_ShowString(258,43,200,16,16,"TIM/div",BLACK,POINT_COLOR);
	LCD_ShowString(258,20,200,16,16,arr_F[scan_flag-1],BLACK,POINT_COLOR);	
	LCD_ShowString(258,60,200,16,16,arr_V[magnitude_flag-1],BLACK,POINT_COLOR);
	LCD_ShowString(258,84,200,16,16,arr_move[flag_move],BLACK,POINT_COLOR);
	LCD_ShowString(260,107,200,16,16," load",BLACK,POINT_COLOR);
	LCD_ShowString(260,130,200,16,16,arr_C[C_dc_ac],BLACK,POINT_COLOR);
	LCD_ShowString(290,130,200,16,16,arr_JDQ[change_gain],BLACK,POINT_COLOR);
	LCD_ShowString(265,153,200,16,16,arr_gain[gain-1],BLACK,POINT_COLOR);
	
	LCD_DrawRectangle(257,174,281,195,BLUE);
	LCD_DrawRectangle(290,174,314,195,BLUE);
	LCD_ShowString(258,176,200,16,16," +",BLACK,POINT_COLOR);
	LCD_ShowString(291,176,200,16,16," -",BLACK,POINT_COLOR);
	
}

void draw_point(u16 a,u16 b,u16 color)
{
	LCD_Fast_DrawPoint(a,200-b,color);
}

void draw_line(u16 x1,u16 y1,u16 x2,u16 y2,u16 color)
{
	LCD_DrawLine(x1,200-y1,x2,200-y2,color);	
}

void Grid(void)
{
	u16 index_y = 0;
	u16 index_hang = 0;	

	POINT_COLOR = BLUE;		
	for(index_hang = 0;index_hang< 250;index_hang = index_hang + 25)
	{
		for(index_y = 0;index_y<200;index_y = index_y +5)
		{
			draw_point(index_hang,index_y,POINT_COLOR);	
		}
	}
	for(index_hang = 0;index_hang<200;index_hang = index_hang + 25)
	{
		for(index_y = 0;index_y<250;index_y = index_y +5)
		{
			draw_point(index_y,index_hang,POINT_COLOR);
		}
	}
	POINT_COLOR = BLUE;
	LCD_DrawRectangle(0,0,250,200,POINT_COLOR);
	draw_line(0,100,250,100,POINT_COLOR);
	draw_line(125,0,125,200,POINT_COLOR);
}

void load_data(void)
{
	int i;
	for(i = 0;i<640;i++)
	{
		USART1->DR = (u8)(ADC_BUFF[i]>>8);
		while((USART1->SR&0X40)==0);
		USART1->DR = (u8)(ADC_BUFF[i]<<8>>8);
		while((USART1->SR&0X40)==0);
	}
}

void set_io1(void)
{
	GPIO_SetBits(GPIOC,GPIO_Pin_2);	
	GPIO_SetBits(GPIOC,GPIO_Pin_1);
	GPIO_SetBits(GPIOC,GPIO_Pin_0);
}
void set_io2(void)
{
	GPIO_SetBits(GPIOC,GPIO_Pin_2);	
	GPIO_SetBits(GPIOC,GPIO_Pin_1);
	GPIO_ResetBits(GPIOC,GPIO_Pin_0);
}
void set_io3(void)					  										
{
	GPIO_SetBits(GPIOC,GPIO_Pin_2);
	GPIO_ResetBits(GPIOC,GPIO_Pin_1);
	GPIO_SetBits(GPIOC,GPIO_Pin_0);
}
void set_io4(void)
{
	GPIO_SetBits(GPIOC,GPIO_Pin_2);	
	GPIO_ResetBits(GPIOC,GPIO_Pin_1);
	GPIO_ResetBits(GPIOC,GPIO_Pin_0);
}
void set_io5(void)
{
	GPIO_ResetBits(GPIOC,GPIO_Pin_2);	
	GPIO_SetBits(GPIOC,GPIO_Pin_1);
	GPIO_SetBits(GPIOC,GPIO_Pin_0);
}
void set_io6(void)
{
	GPIO_ResetBits(GPIOC,GPIO_Pin_2);	
	GPIO_SetBits(GPIOC,GPIO_Pin_1);
	GPIO_ResetBits(GPIOC,GPIO_Pin_0);
}
void set_io7(void)
{
	GPIO_ResetBits(GPIOC,GPIO_Pin_2);	
	GPIO_ResetBits(GPIOC,GPIO_Pin_1);
	GPIO_SetBits(GPIOC,GPIO_Pin_0);
}
void set_io8(void)
{
	GPIO_ResetBits(GPIOC,GPIO_Pin_2);	
	GPIO_ResetBits(GPIOC,GPIO_Pin_1);
	GPIO_ResetBits(GPIOC,GPIO_Pin_0);
}

void c_gain(int flag)
{
	switch(flag)
	{
		case 0:
			GPIO_SetBits(GPIOC,GPIO_Pin_7);
			switch(gain)
				{	
					case 1:set_io1();break;
					case 2:set_io2();break;
					case 3:set_io3();break;
					case 4:set_io4();break;
					case 5:set_io5();break;
					case 6:set_io6();break;
					case 7:set_io7();break;
					case 8:set_io8();break;
					default :break;
				}
				multiple =1/(gain_multiple0[gain-1]);
			break;
		case 1:
			GPIO_ResetBits(GPIOC,GPIO_Pin_7);
			switch(gain)
			{	
				case 1:set_io1();break;
				case 2:set_io2();break;
				case 3:set_io3();break;
				case 4:set_io4();break;
				case 5:set_io5();break;
				case 6:set_io6();break;
				case 7:set_io7();break;
				case 8:set_io8();break;
				default :break;
			}
			multiple =1/(gain_multiple1[gain-1]);
			break;
		default:
			break;
	}	
}

void c_acdc(int flag)
{
	switch(flag)
	{
		case 0:
			GPIO_SetBits(GPIOC,GPIO_Pin_8);
			break;
		case 1:
			GPIO_ResetBits(GPIOC,GPIO_Pin_8);
			break;
		default:
			break;
	}	
}

void c_multiple(int flag)
{
	switch(flag)
	{
		case 0:
			break;
		case 1:
			break;
		case 2:
			break;
		case 3:
			break;
		case 4:
			break;
		case 5:
			break;
		case 6:
			break;
		case 7:
			break;
		default:
			break;
	}	
}

