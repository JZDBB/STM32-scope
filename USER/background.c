#include "background.h"
#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "led.h"
#include "lcd.h"
#include "adc.h"

u8 arr_F[13][8] = {"  5us\0"," 10us\0"," 20us\0"," 50us\0","100us\0","200us\0","500us\0","  1ms\0","  2ms\0","  5ms\0"," 10ms\0"," 20ms\0"," 50ms\0"};
u8 arr_V[7][8] = {"100mV\0","200mV\0","500mV\0","   1V\0","   2V\0","   5V\0","  10V\0"};
u8 arr_gain[8][6] = {"0 0 0\0","0 0 1\0","0 1 0\0","0 1 1\0","1 0 0\0","1 0 1\0","1 1 0\0","1 1 1\0"};
u8 arr_C[2][10] = {" AC\0", " DC\0"};
u8 arr_move[2][9] ={"mov_hor\0","mov_ver\0"};
u8 arr_JDQ[2][3] = {" 0\0"," 1\0"};
float gain_num[8] = {0.05, 0.1, 0.2, 0.4, 8, 10, 20, 25};
float gain_multiple0[8] = {0.036,0.063,0.12,0.226,0.49,0.57,1.13,3};
float gain_multiple1[8] = {0.264,0.54,1.05,2.2,4.2,5.2,9.85,24};
u8 show_gain0[8][8] = {"0.025\0","0.05 \0","0.1  \0","0.2  \0","0.4  \0","0.5  \0","1    \0","2.5  \0"};
u8 show_gain1[8][8] = {"0.25 \0","0.5  \0","1    \0","2    \0","4    \0","5    \0","10   \0","25   \0"};

void set_background()
{
	POINT_COLOR = BLUE;
	
	LCD_DrawRectangle(0,0,250,200,POINT_COLOR);
	LCD_DrawLine(0,100,250,100,POINT_COLOR);
	LCD_DrawLine(125,0,125,200,POINT_COLOR);

	POINT_COLOR=RED;
	LCD_DrawRectangle(0,202,320,240,RED);
	LCD_ShowString(5,203,200,16,16,"V(V):",BLACK,POINT_COLOR);
	LCD_ShowString(5,220,200,16,16,"Vpp(V):",BLACK,POINT_COLOR);
	LCD_ShowString(160,203,200,16,16,"Freq(Hz):",BLACK,POINT_COLOR);
	LCD_ShowString(160,220,200,16,16,"duty(%):",BLACK,POINT_COLOR);

	POINT_COLOR=WHITE;
	LCD_DrawRectangle(252,0,320,200,WHITE);
	LCD_DrawRectangle(255,2,316,38,BLUE);
	LCD_DrawRectangle(255,42,316,78,BLUE);
	LCD_DrawRectangle(255,82,316,101,BLUE);
	LCD_DrawRectangle(255,105,316,124,BLUE);
	LCD_DrawRectangle(255,2,316,38,WHITE);
	POINT_COLOR=BLUE;
	LCD_ShowString(257,3,200,16,16,"VOL/div",BLACK,POINT_COLOR);	
	LCD_ShowString(257,43,200,16,16,"TIM/div",BLACK,POINT_COLOR);
	LCD_ShowString(257,20,200,16,16,arr_F[5],BLACK,POINT_COLOR);	
	LCD_ShowString(257,60,200,16,16,arr_V[3],BLACK,POINT_COLOR);
	LCD_ShowString(257,85,200,16,16,arr_move[0],BLACK,POINT_COLOR);
	LCD_ShowString(257,108,200,16,16,"load",BLACK,POINT_COLOR);
	
}
