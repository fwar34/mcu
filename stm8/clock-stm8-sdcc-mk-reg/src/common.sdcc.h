#ifndef _COMMON_H_
#define _COMMON_H_
#include "iostm8.h"

extern unsigned char current_setting;//当前设置项
//current_setting可以作为下标来取，秒不用设置，所以不在数组里面
extern unsigned char ds1302_reg_addr[11];
extern unsigned char beep_setting;//beep开关
extern unsigned char hex_array[16];
extern unsigned char uart_recv_buf[256];
extern unsigned char uart_recv_buf_index;

extern uint16_t debug_ir;

#define LCD_BK_PIN PC_ODR_ODR2

#define BEEP_PIN PD_ODR_ODR4
#define beep_ring() PD_ODR_ODR4 = 0
#define beep_mute() PD_ODR_ODR4 = 1

#define LED_PIN PA_ODR_ODR2


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
extern DS1302_TIME current_time;

void beep_ring_1s();
void common_gpio_init();
void clear_uart_recv_buf();

#endif
