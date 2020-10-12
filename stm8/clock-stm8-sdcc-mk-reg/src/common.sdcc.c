#include "common.sdcc.h"
#include "delay.h"

unsigned char current_setting;//当前设置项
//current_setting可以作为下标来取，秒不用设置，所以不在数组里面
/* unsigned char ds1302_reg_addr[11] = {0, 0x82, 0x84, 0x86, 0x88, 0x8a, 0x8c, 0x8e, 0x90, 0xbe, 0xc0}; */
unsigned char beep_setting;//beep开关
unsigned char hex_array[16] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'};
unsigned char uart_recv_buf[256];
unsigned char uart_recv_buf_index = 0;
DS1302_TIME current_time;

uint16_t debug_ir = 0;


//蜂鸣器提醒声
void beep_ring_1s()
{
    if (beep_setting) {
        unsigned char i = 0;
        for (;i < 100;++i) {
            delay_us(100);
            BEEP_PIN = !BEEP_PIN;
        }
        beep_mute();
    }
}

void common_gpio_init()
{
    //LED
    PA_DDR |= 1 << 2;
    PA_CR1 |= 1 << 2;
    PA_CR2 |= 1 << 2;
    PA_ODR |= 1 << 2;

    //BEEP
    PD_DDR_DDR4 = 1;
    PD_CR1_C14 = 1;
    PD_CR2_C24 = 1;
    PD_ODR_ODR4 = 1;

    //lcd light
    PC_DDR_DDR2 = 1;
    PC_CR1_C12 = 1;
    PC_CR2_C22 = 1;
    PC_ODR_ODR2 = 1;
}

void clear_uart_recv_buf()
{
    uart_recv_buf_index = 0;
    for (unsigned char i = 0; i < 255; ++i) {
        uart_recv_buf[i] = '\0';
    }
}
