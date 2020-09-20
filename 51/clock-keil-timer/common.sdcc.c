#include "common.sdcc.h"
#include "delay.sdcc.h"

unsigned char current_setting;//当前设置项
//current_setting可以作为下标来取，秒不用设置，所以不在数组里面
/* unsigned char ds1302_reg_addr[11] = {0, 0x82, 0x84, 0x86, 0x88, 0x8a, 0x8c, 0x8e, 0x90, 0xbe, 0xc0}; */

bit beep_setting = 1;//beep开关


//蜂鸣器提醒声
void beep_ring_1s()
{
    if (beep_setting) {
        unsigned char i = 0;
        for (;i < 100;++i) {
            Delay100us();
            beep = !beep;
        }
        beep = 1;
    }
}
