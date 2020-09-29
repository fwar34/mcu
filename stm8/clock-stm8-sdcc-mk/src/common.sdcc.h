#ifndef _COMMON_H_
#define _COMMON_H_
#include <stm8s.h>

extern unsigned char current_setting;//当前设置项
//current_setting可以作为下标来取，秒不用设置，所以不在数组里面
extern unsigned char ds1302_reg_addr[11];

extern unsigned char beep_setting;//beep开关
#define lcd_light_back GPIO_PIN_2; //PC
#define beep GPIO_PIN_4; //PD
#define led GPIO_PIN_2; //PA

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

#endif
