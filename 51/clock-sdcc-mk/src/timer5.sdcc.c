#include "common.sdcc.h"

void Timer5Init(void)//1.085微秒@11.0592MHz
{
    AUXR &= 0xFB;//定时器时钟12T模式
    /* T2L = 0xFF;//设置定时初值 */
    /* T2H = 0xFF;//设置定时初值 */
    /* AUXR |= 0x10;//定时器2开始计时 */
}
