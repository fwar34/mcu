//#include <stc8.h>
#include "ds1302.sdcc.h"
#include "lcd1602.sdcc.h"
#include "dht11.sdcc.h"
#include "delay.sdcc.h"
#include "infrared.sdcc.h"
#include "common.sdcc.h"
#include "uart_sdcc.h"

void tm0_isr() __interrupt 1;
extern void Timer0Init(void);//50毫秒@11.0592MHz
extern void Timer1Init(void); //dht11和ir在使用
extern void Timer3Init(void);

extern unsigned int new_value;

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
    /* unsigned char msg[] = "hello"; */
    //初始时间20年8月16号14点16分55秒星期天
    DS1302_TIME start_time = {20, 9, 9, 3, 0, 6, 40};

    P_SW2 = 0x80;
    XOSCCR = 0xc0;//启动外部晶振
    while (!(XOSCCR & 1));//等待时钟稳定
    CLKDIV = 0x00;//时钟不分频
    CKSEL = 0x01;//选择外部晶振
    P_SW2 = 0x00;

    initLcd1602();
    ds1302_init();
    UartInit();

    if (!ds1302_is_running()) {
        ds1302_write_time(&start_time);
    }

    Timer0Init(); //
    Timer1Init(); //dht11 use
    /* Timer3Init(); */
    beep_mute();
    IrInit();
    lcd_light_back = 1;

    while (1)
    {
        display_idle_count();

        /* ds1302_read_time(&current_time); */
        /* display(&current_time); */
    }
}
