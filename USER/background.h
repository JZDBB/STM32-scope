#ifndef __BACKGROUND_H
#define __BACKGROUND_H
#include <sys.h> 


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

#endif