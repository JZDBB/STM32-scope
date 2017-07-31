#ifndef __BACKGROUND_H
#define __BACKGROUND_H
#include <sys.h> 

extern u16 num_scan;
extern float gao_pin_palus;
extern u16 vcc_div;
extern u16 vpp;
extern int ver;
extern int hor;
extern float arr_plot[250];
extern int flag_move;
extern int gain;
extern u8 C_dc_ac;
extern u8 change_gain;
extern u8 pause;
extern int selected;
extern u8 magnitude_flag;
extern long int scan_flag;
extern int update;
extern int n;
extern int flag_inc;
extern int flag_dec;
extern int flag_load;
extern int flag_mov;
extern int flag_acdc;
extern int flag_gain;

extern u16 V[7];
extern u16 F[13];
extern u8 arr_F[13][8];
extern u8 arr_V[7][8];
extern u8 arr_gain[8][6];
extern u8 arr_JDQ[2][3];
extern float gain_multiple0[8];
extern float gain_multiple1[8];
extern u8 show_gain0[8][8];
extern u8 show_gain1[8][8];
extern u8 arr_move[2][9];
extern u8 arr_C[2][10];

void set_background(void);
void draw_point(u16 a,u16 b,u16 color);
void draw_line(u16 x1,u16 y1,u16 x2,u16 y2,u16 color);
void Grid(void);
void load_data(void);
#endif
