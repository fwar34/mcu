#include <mcs51/8051.h>
#include "uart_sdcc.h"
#include "common.sdcc.h"

/*
 * 延时
 */
void delay(uint16_t n)
{
    while (n--);
}

/*
 * UART初始化
 * 波特率：9600
 */
void UART_init()
{
    SCON = 0x50;//8位数据,可变波特率
    AUXR &= 0xBF;//定时器1时钟为Fosc/12,即12T
    AUXR &= 0xFE;//串口1选择定时器1为波特率发生器
    TMOD &= 0x0F;//设定定时器1为16位自动重装方式
    TL1 = 0xE8;//设定定时初值
    TH1 = 0xFF;//设定定时初值
    ET1 = 0;//禁止定时器1中断
    TR1 = 1;//启动定时器1
}

/*
 * UART 发送一字节
 */
void UART_send_byte(uint8_t dat)
{
    SBUF = dat;
    while (TI == 0);
    TI = 0;
}

/*
 * UART 发送字符串
 */
void UART_send_string(uint8_t *buf)
{
    while (*buf != '\0')
    {
        UART_send_byte(*buf++);
    }
}
