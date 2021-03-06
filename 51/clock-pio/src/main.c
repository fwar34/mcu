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

void tm0_isr() __interrupt(1);
extern void Timer0Init(void);//50毫秒@11.0592MHz
extern unsigned short idle_count;//最后一次设置开始空闲计数
extern unsigned int new_value;

extern unsigned char ch_count;//两次ch键进入设置的时间计数

#define led P0_5

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
    /* unsigned char msg[] = "hello"; */
    //初始时间20年8月16号14点16分55秒星期天 
    DS1302_TIME start_time = {20, 9, 9, 3, 0, 6, 40};
    DS1302_TIME current_time;

    P_SW2 = 0x80;
    XOSCCR = 0xc0;//启动外部晶振
    while (!(XOSCCR & 1));//等待时钟稳定
    CKDIV = 0x00;//时钟不分频
    CKSEL = 0x01;//选择外部晶振
    P_SW2 = 0x00;

    /*P0M1 = 0x00;
      P0M0 = 0x00;

      P1M1 = 0x00;         
      P1M0 = 0x00;

      P2M1 = 0x00;
      P2M0 = 0x00;

      P3M1 = 0x00;
      P3M0 = 0x00;

      P4M1 = 0x00;
      P4M0 = 0x00;

      P5M1 = 0x00;
      P5M0 = 0x00;

      P6M1 = 0x00;
      P6M0 = 0x00;

      P7M1 = 0x00;
      P7M0 = 0x00;*/
    
    initLcd1602();
    ds1302_init();
    UART_init();

    if (!ds1302_is_running()) {
        ds1302_write_time(&start_time);
    }

    Timer0Init();
    beep_mute();
    IrInit();
    lcd_light_back = 1;
    
    while (1)
    {
        /* UART_send_string("ok"); */
        display_current_setting();
        display_idle_count();
        if (current_setting) {
            enter_settings();
        } else {
            ds1302_read_time(&current_time);
            display(&current_time);
        }
        display_dht11();
        
        //lcd_light_back = !lcd_light_back;
        //led = !led;
        //Delay1000ms();
        /* P0_5 = !P0_5; */
    }
}
