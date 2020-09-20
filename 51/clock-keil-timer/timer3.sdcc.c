#if 0
#include "common.sdcc.h"
#include "uart_sdcc.h"

unsigned int count3 = 0;
extern void IrReceive();

sbit ledd = P0 ^ 5;

void Timer3Init(void)//56微秒@11.0592MHz
{
    T4T3M &= 0xFD;//定时器时钟12T模式
    T3L = 0xCC;//设置定时初值
    T3H = 0xFF;//设置定时初值
    T4T3M |= 0x08;//定时器3开始计时

    IE2 = ET3;                                  //使能定时器中断
    EA = 1;
}

void tm3_Isr() interrupt 19
{
    //AUXINTIF &= ~T3IF;                          //清中断标志
    if (++count3 >= 20000) {
        ledd = !ledd;
    }
    IrReceive();
}
#endif