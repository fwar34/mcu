#include "stm8s.h"
#include "uart_sdcc.h"
#include "common.sdcc.h"

/*
 * 延时
 */
void delay(unsigned int n)
{
    while (n--);
}

void uart_init()//9600bps@16Mhz
{
}

/*
 * UART 发送一字节
 */
void uart_send_byte(unsigned char dat)
{
    /* SBUF = dat; */
    /* while (TI == 0); */
    /* TI = 0; */
}

/*
 * UART 发送字符串
 */
void uart_send_string(unsigned char* buf)
{
    /* while (*buf != '\0') */
    /* { */
    /*     UART_send_byte(*buf++); */
    /* } */
}
