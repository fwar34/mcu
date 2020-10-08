#ifndef _COMMON_H_
#define _COMMON_H_
#include "stm8s.h"

extern unsigned char current_setting;//当前设置项
//current_setting可以作为下标来取，秒不用设置，所以不在数组里面
extern unsigned char ds1302_reg_addr[11];
extern unsigned char beep_setting;//beep开关
extern unsigned char hex_array[16];
extern unsigned char uart_recv_buf[256];
extern unsigned char uart_recv_buf_index;

#define LCD_BK_PORT GPIOC
#define LCD_BK_PIN GPIO_PIN_2

#define BEEP_PORT GPIOD
#define BEEP_PIN GPIO_PIN_4
#define beep_ring() GPIO_WriteLow(BEEP_PORT, BEEP_PIN)
#define beep_mute() GPIO_WriteHigh(BEEP_PORT, BEEP_PIN)

#define LED_PORT GPIOA
#define LED_PIN GPIO_PIN_2


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
void common_gpio_init();
void clear_uart_recv_buf();

#endif
