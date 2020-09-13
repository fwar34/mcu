#include "ds1302.h"
#include "lcd1602.h"
#include "dht11.h"
#include "delay.h"
#include "infrared.h"
#include "common.h"

extern void Timer0Init(void);		//50毫秒@11.0592MHz
extern unsigned short idle_count; //最后一次设置开始空闲计数

extern unsigned char ch_count; //两次ch键进入设置的时间计数
void display_current_setting()
{
    write_char(0, 13, current_setting + '0');
}

void display_idle_count()
{
    unsigned char i = idle_count / 10;
    unsigned char j = idle_count % 10;
    write_char(0, 14, i + '0');
    write_char(0, 15, j + '0');
}

void main(void)
{
    //初始时间20年8月16号14点16分55秒星期天 
    DS1302_TIME start_time = {20, 9, 9, 3, 0, 6, 40};
    DS1302_TIME current_time;
    initLcd1602();
    ds1302_init();

    if (!ds1302_is_running()) {
        ds1302_write_time(&start_time);
    }

    Timer0Init();
    beep_mute();
    IrInit();
    
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
        display_dht11();
    }
}
