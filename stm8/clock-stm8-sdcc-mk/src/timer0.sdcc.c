#include "dht11.sdcc.h"
#include "key.sdcc.h"
#include "ds1302.sdcc.h"
#include "common.sdcc.h"
#include "uart_sdcc.h"
#include "lcd1602.sdcc.h"

extern unsigned char ch_count;//两次ch键进入设置的时间计数
extern __bit first_ch_flag;//表示第一次按ch的标志
extern unsigned char dht11_data[5];//湿度十位，湿度个位，温度十位，温度个位，是否显示的标志
extern unsigned short idle_count;//最后一次设置开始空闲计数

static unsigned char count = 40;//dht11更新的计数
DS1302_TIME current_time;

void Timer0Init(void)        //50毫秒@11.0592MHz
{
    TMOD &= 0xF0;
    TMOD |= 0x01;                    //set timer0 as mode1 (16-bit)
    TH0 = 0x4C;
    TL0 = 0x00;

    TF0 = 0;     //清除TF0标志
    ET0  = 1;                           //enable timer0 interrupt

    /* TR0 = 1;     //定时器0开始计时 */
    EA  = 1;                           //open global interrupt switch
}

/* https://zhidao.baidu.com/question/477148677.html */
/* void Timer0Delay1s() interrupt 1 */
/* { */
/*     static unsigned char count; */
/*     TH0 = (65535 - 50000) / 256; */
/*     TL0 = (65535 - 50000) % 256; */
/*     if (count ++ == 20) { */
/*         count = 0; */
/*         //TODO */
/*     } */
/* } */

/* Timer0 interrupt routine */
/* void tm0_isr() __interrupt(1)  也可以*/
void tm0_isr() __interrupt 1
{
    ds1302_read_time(&current_time);
    display(&current_time);
        
    if (ch_count > 0) {//第一次点击ch按钮会把ch_count设置成1
        ++ch_count;
        if (ch_count > 20) {//1s过后没有点击第二次ch按钮的话重置字段
            ch_count = 0;
        }
    }

    if (idle_count > 0) {//每一次设置会把idle_count设置成1,所以大于0才判断是否是设置空闲超时
        ++idle_count;
        if (idle_count > 20 * 10) {//设置空闲了10秒之后退出
            idle_count = 0;
            exit_settings();
        }
    }

    if (++count >= 20 * 2) {//1000ms * 2 -> 2s更新一次dht11
        /* lcd_light_back = !lcd_light_back; */
        count = 0;//reset counter
        dht11_read_data();
        display_dht11();
    }

    process_key();//处理物理按键
}
