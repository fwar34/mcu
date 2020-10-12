#include "dht11.sdcc.h"
#include "key.sdcc.h"
#include "ds1302.sdcc.h"
#include "common.sdcc.h"
#include "uart_sdcc.h"
#include "lcd1602.sdcc.h"
#include "task.h"

void Timer0Init(void)        //1毫秒@11.0592MHz
{
    TMOD &= 0xF0;
    TMOD |= 0x01;                    //set timer0 as mode1 (16-bit)
    /* TH0 = 0x4C; */
    /* TL0 = 0x00; */
    /* TH0 = 0x4C; */
    /* TL0 = 0x00; */
    
    TL0 = 0x66;//设置定时初值
    TH0 = 0xFC;//设置定时初值

    TF0 = 0;     //清除TF0标志
    ET0  = 1;                           //enable timer0 interrupt

    /* TR0 = 1;     //定时器0开始计时 */
    EA  = 1;                           //open global interrupt switch
}

void tm0_isr() __interrupt 1
{
    CheckTask();
}
