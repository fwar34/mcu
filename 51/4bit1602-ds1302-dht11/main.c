#include "ds1302.h"
#include "lcd1602.h"
#include "dht11.h"
#include "delay.h"
#include "infrared.h"
#include "common.h"

extern unsigned char dht11_data[5]; //湿度十位，湿度个位，温度十位，温度个位，是否更新显示的标志
extern void Timer0Init(void); //50毫秒@12.000MHz


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
        if (current_setting) {
            enter_settings();
        } else {
            ds1302_read_time(&current_time);
            display(&current_time);
        }
        display_dht11();
    }
}
