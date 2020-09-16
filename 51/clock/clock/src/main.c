/**
 * 软件 UART：
 *      TX 引脚：P31
 *      波特率：9600
*/

#include "config.h"
#include "soft_uart.h"
#include "delay.h"

void main()
{
    while (1)
    {
        LOG("Hello, STC15F104W\n");
        delay_ms(200);
    }
}
