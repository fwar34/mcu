#ifndef _COMMON_H_
#define _COMMON_H_
#include <reg52.h>

extern unsigned char current_setting; //当前设置项
//current_setting可以作为下标来取，秒不用设置，所以不在数组里面
extern unsigned char ds1302_reg_addr[11];

sbit lcd_light_back = P0 ^ 3;
sbit beep = P3 ^ 7;
extern bit beep_setting; //beep开关

#define beep_ring() beep = 0
#define beep_mute() beep = 1

void beep_ring_1s();

#endif
