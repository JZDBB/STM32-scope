#ifndef __BACKGROUND_H
#define __BACKGROUND_H
#include <sys.h> 

extern u8 frequency_flag;
extern long int shao_miao_shu_du;
extern u8 num_shao_miao;
extern u8 mode1;
extern u8 mode2;
extern u8 num_fu_du;
extern float gao_pin_palus;
extern u16 vcc_div;
extern u16 vpp;
extern int ver;
extern int hor;
extern float arr_plot[250];
extern int flag;
extern int inter;
extern int flag_mode;
extern int gain;
extern u8 C_dc_ac;
extern u8 change_gain;
extern u8 pause;

extern u8 arr_F[13][8];
extern u8 arr_V[7][8];
extern u8 arr_gain[8][6];
extern u8 arr_JDQ[2][3];
extern float gain_multiple0[8];
extern float gain_multiple1[8];
extern u8 show_gain0[8][8];
extern u8 show_gain1[8][8];
//extern u8 arr_move[2][10];

void set_background();
void draw_point(u16 a,u16 b,u16 color);
void draw_line(u16 x1,u16 y1,u16 x2,u16 y2,u16 color);
void Grid(void);

#endif