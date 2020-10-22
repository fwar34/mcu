#include <stdio.h>
#include "iostm8.h"
#include "uart.h"

/*
 * Initialize the UART to requested baudrate, tx/rx, 8N1.
 */
void uart_init()
{
  UART2_CR1=0x00;//1个起始位，8个数据位，无校验位
  UART2_CR2=0x2c;//接收中断使能，使能发送、接收
  UART2_CR3=0x00;//1个停止位
  //设置波特率近似115200
  UART2_BRR2=0x0B;
  UART2_BRR1=0x08;
}

void uart_send_byte(unsigned char Data)
{
    while ((UART2_SR & 0x80) == 0);
    UART2_DR = Data;
} 

/**
 * \b uart_putchar
 *
 * Write a char out via UART2
 *
 * @param[in] c Character to send
 *
 * @return Character sent
 */
char uart_putchar (char c)
{
    /* Convert \n to \r\n */
    if (c == '\n')
        putchar('\r');

    /* Write a character to the UART2 */
    uart_send_byte(c);
      
    return (c);
}

int putchar (int c)
{
    return(uart_putchar(c));
}
