#include "common.sdcc.h"

void Timer3Init(void)//56微秒@11.0592MHz
{
    T4T3M &= 0xFD;//定时器时钟12T模式
    /* T3L = 0xCC;//设置定时初值 */
    /* T3H = 0xFF;//设置定时初值 */
    /* T4T3M |= 0x08;//定时器3开始计时 */
    T4T3M &= 0xF7;//定时器3暂停计时

    /* IE2 = ET3;                                  //使能定时器中断 */
    /* EA = 1; */
}
