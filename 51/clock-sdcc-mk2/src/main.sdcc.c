//#include <stc8.h>
#include "ds1302.sdcc.h"
#include "lcd1602.sdcc.h"
#include "dht11.sdcc.h"
#include "delay.sdcc.h"
#include "infrared.sdcc.h"
#include "common.sdcc.h"
#include "uart_sdcc.h"


#define CKSEL (*(unsigned char volatile __xdata *)0xfe00)
#define CKDIV (*(unsigned char volatile __xdata *)0xfe01)
#define IRC24MCR (*(unsigned char volatile __xdata *)0xfe02)
#define XOSCCR (*(unsigned char volatile __xdata *)0xfe03)
#define IRC32KCR (*(unsigned char volatile __xdata *)0xfe04)

void IrInit();
void tm0_isr() __interrupt 1;
void IrRead() __interrupt 2;
/* void tm3_Isr() __interrupt 19; */
extern void Timer0Init(void);//50毫秒@11.0592MHz
extern void Timer1Init(void);
extern void Timer3Init(void);//56微秒@11.0592MHz
extern unsigned short idle_count;//最后一次设置开始空闲计数
extern unsigned int new_value;

extern unsigned char ch_count;//两次ch键进入设置的时间计数

#define led P0_5

__bit dht11_flag = 0;

void display_current_setting()
{
    write_char(0, 13, current_setting + '0');
}

void display_idle_count()
{
    /* unsigned char i = idle_count / 10; */
    /* unsigned char j = idle_count % 10; */
    unsigned char i = new_value / 10;
    unsigned char j = new_value % 10;
    write_char(0, 14, i + '0');
    write_char(0, 15, j + '0');
}

void main(void)
{
    //初始时间20年8月16号14点16分55秒星期天 
    DS1302_TIME start_time = {20, 9, 9, 3, 0, 6, 40};
    DS1302_TIME current_time;

    P_SW2 = 0x80;
    XOSCCR = 0xc0;//启动外部晶振
    while (!(XOSCCR & 1));//等待时钟稳定
    CKDIV = 0x00;//时钟不分频
    CKSEL = 0x01;//选择外部晶振
    P_SW2 = 0x00;
    
    initLcd1602();
    ds1302_init();
    UartInit();
    IrInit();

    if (!ds1302_is_running()) {
        ds1302_write_time(&start_time);
    }

    Timer0Init(); //
    Timer1Init(); //dht11 use
    Timer3Init(); //ir use
    beep_mute();
    lcd_light_back = 1;

    while (1)
    {
        display_current_setting();
        display_idle_count();
        if (current_setting) {
            enter_settings();
        } else {
            ds1302_read_time(&current_time);
            display(&current_time);
        }

        if (dht11_flag) {
            dht11_flag = 0;
            dht11_read_data();
            display_dht11();
        }
    }
}
