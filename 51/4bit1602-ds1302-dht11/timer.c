#include <stc12c5a60s2.h>
#include "dht11.h"
#include "key.h"


sbit led = P3 ^ 7;
extern unsigned char dht11_data[5]; //湿度十位，湿度个位，温度十位，温度个位，是否显示的标志

static unsigned short count = 0;
static unsigned short idle_count = 0;

void Timer0Init(void)//50毫秒@12.000MHz
{
    AUXR &= 0x7F;//定时器时钟12T模式
    TMOD &= 0xF0;//设置定时器模式
    TL0 = 0xB0;//设置定时初值
    TH0 = 0x3C;//设置定时初值
    TF0 = 0;//清除TF0标志
    TR0 = 1;//定时器0开始计时

    ET0  = 1;                           //enable timer0 interrupt
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
void tm0_isr() interrupt 1
{
    //TL0 = 0xB0;//设置定时初值
    //TH0 = 0x3C;//设置定时初值
    /* TL0 = T1MS;                           //reload timer0 low byte */
    /* TH0 = T1MS >> 8;                  //reload timer0 high byte */
    if (++count == 400) {                //50ms * 400 -> 2s
        count = 0;                //reset counter
        if (!dht11_read_data()) { 
            //read success
            dht11_data[5] = 1;
        }
        led = !led;
    }

    if (process_key() && current_setting) {
        if (++idle_count == 400 * 5) { //10秒钟不再设置就重置current_setting
            current_setting = 0;
            idle_count = 0;
        }
    }
}
