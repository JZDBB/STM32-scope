#include "background.h"
#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "led.h"
#include "lcd.h"
#include "adc.h"

u8 arr_F[13][11] = {"  5us/div\0"," 10us/div\0"," 20us/div\0"," 50us/div\0","100us/div\0","200us/div\0","500us/div\0","  1ms/div\0","  2ms/div\0","  5ms/div\0"," 10ms/div\0"," 20ms/div\0"," 50ms/div\0"};
u8 arr_V[7][11] = {"100mV/div\0","200mV/div\0","500mV/div\0","   1V/div\0","   2V/div\0","   5V/div\0","  10V/div\0"};
u8 arr_gain[8][6] = {"0 0 0\0","0 0 1\0","0 1 0\0","0 1 1\0","1 0 0\0","1 0 1\0","1 1 0\0","1 1 1\0"};
u8 arr_C[2][10] = {" AC\0", " DC\0"};
//u8 arr_f[10] = "  5us/div";
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
	//GUI_Show12ASCII(262,210,"Vmax:",POINT_COLOR,YELLOW);
	//GUI_Show12ASCII(262,210,"Vmin:",POINT_COLOR,YELLOW);
	LCD_ShowString(5,220,200,16,16,"Vpp(V):",BLACK,POINT_COLOR);
	LCD_ShowString(160,203,200,16,16,"Freq(Hz):",BLACK,POINT_COLOR);
	LCD_ShowString(160,220,200,16,16,"duty(%):",BLACK,POINT_COLOR);
	
	/*POINT_COLOR=BLUE;
	LCD_DrawRectangle(348,0,399,200,WHITE);
	LCD_DrawRectangle(351,2,396,20,POINT_COLOR);
	LCD_DrawRectangle(351,30,396,66,POINT_COLOR);
	LCD_DrawRectangle(351,76,396,112,POINT_COLOR);
	LCD_ShowString(354,4,200,16,16,arr_C[0],POINT_COLOR,BLACK);
	LCD_ShowString(354,32,200,16,16," SJ ",POINT_COLOR,BLACK);
	LCD_ShowString(354,78,200,16,16,"C B A",POINT_COLOR,BLACK);
	LCD_ShowString(354,94,200,16,16,arr_gain[gain-1],BLUE,BLACK);
	LCD_ShowString(354,48,200,16,16,arr_JDQ[change_gain],BLUE,BLACK);
	LCD_ShowString(354,4,200,16,16,arr_C[C_dc_ac],BLUE,BLACK);*/

	POINT_COLOR=WHITE;
	LCD_DrawRectangle(252,0,320,200,WHITE);
	LCD_DrawRectangle(255,2,316,38,BLUE);
	LCD_DrawRectangle(255,42,316,80,BLUE);
	LCD_DrawRectangle(255,84,316,103,BLUE);
	LCD_DrawRectangle(255,107,316,126,BLUE);
	LCD_DrawRectangle(255,2,316,38,WHITE);
	POINT_COLOR=BLUE;
	LCD_ShowString(257,3,200,16,16,"VOL/div",BLACK,POINT_COLOR);	
	LCD_ShowString(257,43,200,16,16,"TIM/div",BLACK,POINT_COLOR);
	LCD_ShowString(257,85,200,16,16,arr_move[0],BLACK,POINT_COLOR);
	LCD_ShowString(257,108,200,16,16,"load",BLACK,POINT_COLOR);
}
