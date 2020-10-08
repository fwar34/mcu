#include "common.sdcc.h"
#include "delay.sdcc.h"
#include "delay.h"

unsigned char current_setting;//当前设置项
//current_setting可以作为下标来取，秒不用设置，所以不在数组里面
/* unsigned char ds1302_reg_addr[11] = {0, 0x82, 0x84, 0x86, 0x88, 0x8a, 0x8c, 0x8e, 0x90, 0xbe, 0xc0}; */
unsigned char beep_setting;//beep开关
unsigned char hex_array[16] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'};

//蜂鸣器提醒声
void beep_ring_1s()
{
    if (beep_setting) {
        unsigned char i = 0;
        for (;i < 100;++i) {
            delay_us(100);
            GPIO_WriteReverse(BEEP_PORT, BEEP_PIN);
        }
        beep_mute();
    }
}

void common_gpio_init()
{
    GPIO_Init(LED_PORT, LED_PIN, GPIO_MODE_OUT_PP_HIGH_FAST);
    GPIO_Init(BEEP_PORT, BEEP_PIN, GPIO_MODE_OUT_PP_HIGH_FAST);
    GPIO_Init(LCD_BK_PORT, LCD_BK_PIN, GPIO_MODE_OUT_PP_HIGH_FAST);
}
