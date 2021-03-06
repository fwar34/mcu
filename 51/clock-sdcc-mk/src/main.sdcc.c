//#include <stc8.h>
#include "ds1302.sdcc.h"
#include "lcd1602.sdcc.h"
#include "dht11.sdcc.h"
#include "delay.sdcc.h"
#include "infrared.sdcc.h"
#include "common.sdcc.h"
#include "uart_sdcc.h"
#include "key.sdcc.h"
#include "task.h"

void tm0_isr() __interrupt 1;
extern void Timer0Init(void);//50毫秒@11.0592MHz
extern void Timer1Init(void); //dht11和ir在使用
extern void Timer3Init(void);

extern unsigned int new_value;

typedef struct {
    unsigned char bit0:1;
    unsigned char bit1:1;
    unsigned char bit2:1;
    unsigned char bit3:1;
    unsigned char bit4:1;
    unsigned char bit5:1;
    unsigned char bit6:1;
    unsigned char bit7:1;
}Test;

#define __IO_REG8_BIT(NAME, ADDRESS, BIT_STRUCT)        \
    volatile unsigned char __at (ADDRESS) NAME;         \
    volatile BIT_STRUCT __at (ADDRESS) NAME##_bit

volatile unsigned char __at (0x80) PB;
volatile Test __at (0x80) PB_bit;

#define T0 PB_bit.bit0

__IO_REG8_BIT(PA, 0x80, Test);


void display_idle_count()
{
    /* unsigned char i = idle_count / 10; */
    /* unsigned char j = idle_count % 10; */
    UART_send_string("display_idle_count");
    unsigned char i = new_value / 10;
    unsigned char j = new_value % 10;
    /* write_char(0, 14, i + '0'); */
    /* write_char(0, 15, j + '0'); */
}


void main(void)
{
    /* unsigned char msg[] = "hello"; */
    //初始时间20年8月16号14点16分55秒星期天
    DS1302_TIME start_time = {20, 9, 9, 3, 0, 6, 40};
    /* DS1302_TIME current_time; */

    PB = 1;
    PB_bit.bit0 = 1;
    T0 = 1;

    PA = 1;
    PA_bit.bit2 = 1;

    P_SW2 = 0x80;
    XOSCCR = 0xc0;//启动外部晶振
    while (!(XOSCCR & 1));//等待时钟稳定
    CLKDIV = 0x00;//时钟不分频
    CKSEL = 0x01;//选择外部晶振
    P_SW2 = 0x00;

    AddTask(10, ds1302_read_time, 1);
    AddTask(10, display, 1);
    AddTask(1000, display_idle_count, 1);
    AddTask(20, process_key, 1);
    AddTask(2000, dht11_read_data, 1);
    AddTask(2000, display_dht11, 1);

    initLcd1602();
    ds1302_init();
    UartInit();

    if (!ds1302_is_running()) {
        ds1302_write_time(&start_time);
    }

    Timer0Init(); //
    Timer1Init(); //dht11 use
    Timer3Init();
    beep_mute();
    IrInit();
    lcd_light_back = 1;

    wait_for_dht11();
    lcdWriteCmd(0x01); //1602清屏
    TR0 = 1;

    while (1)
    {
        ProcessTask();
    }
}
