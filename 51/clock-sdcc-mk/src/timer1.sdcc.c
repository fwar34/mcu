#include "common.sdcc.h"

void Timer1Init(void)        //timer1@11.0592MHz
{
    TMOD &= 0x0F;
    TMOD |= 0x10;

    //不关心timer1的中断
    TF1 = 0;     //清除TF0标志
    /* ET1  = 1;                           //enable timer1 interrupt */
    TR1 = 0;     //定时器1关闭
    EA  = 1;                           //open global interrupt switch
}
