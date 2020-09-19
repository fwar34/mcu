#ifndef _COMMON_H_
#define _COMMON_H_
#include <mcs51/8051.h>

extern unsigned char current_setting;//当前设置项
//current_setting可以作为下标来取，秒不用设置，所以不在数组里面
extern unsigned char ds1302_reg_addr[11];

extern __bit beep_setting;//beep开关
#define lcd_light_back P0_3
#define beep P0_7

#define beep_ring() beep = 0
#define beep_mute() beep = 1

/* extern struct DS1302_TIME; */
typedef struct _DS1302_TIME
{
    unsigned char year;
    unsigned char month;
    unsigned char day;
    unsigned char week;
    unsigned char hour;
    unsigned char minute;
    unsigned char second;
} DS1302_TIME;

void beep_ring_1s();

__sfr __at (0x94) P0M0;
__sfr __at (0x93) P0M1;
__sfr __at (0x92) P1M0;
__sfr __at (0x91) P1M1;
__sfr __at (0x96) P2M0;
__sfr __at (0x95) P2M1;
__sfr __at (0xb2) P3M0;
__sfr __at (0xb1) P3M1;
__sfr __at (0xb4) P4M0;
__sfr __at (0xb3) P4M1;
__sfr __at (0xca) P5M0;
__sfr __at (0xc9) P5M1;
__sfr __at (0xcc) P6M0;
__sfr __at (0xcb) P6M1;
__sfr __at (0xe2) P7M0;
__sfr __at (0xe1) P7M1;

__sfr __at (0xba) P_SW2;
__sfr __at (0x8e) AUXR;

#endif
