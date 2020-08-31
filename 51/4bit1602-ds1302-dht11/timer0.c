#include <stc12c5a60s2.h>
#include "dht11.h"

static unsigned short count = 0;

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
    count = 0;
}

void Timer0InitAuto(void)//50毫秒@12.000MHz
{
    AUXR &= 0x7F;//定时器时钟12T模式
    TMOD &= 0xF0;//设置定时器模式
    TMOD |= 0x01;//设置定时器模式
    TL0 = 0xB0;//设置定时初值
    TH0 = 0x3C;//设置定时初值
    TF0 = 0;//清除TF0标志
    TR0 = 1;//定时器0开始计时

    ET0  = 1;                           //enable timer0 interrupt
    EA  = 1;                           //open global interrupt switch
    count = 0;
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
void tm0_isr() interrupt 1 using 1
{
    /* TL0 = T1MS;                           //reload timer0 low byte */
    /* TH0 = T1MS >> 8;                  //reload timer0 high byte */
    if (++count == 400) {                //50ms * 400 -> 2s
        count = 0;                //reset counter
        dht11_read_data();
    }
}
