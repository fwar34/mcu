#include "iostm8s105c6.h"
#include "uart_sdcc.h"

unsigned char hex_array[16] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'};
/*
 * 延时
 */
void delay(unsigned int n)
{
    while (n--);
}

/*波特率=fmaster/UART_DIV，BRR2的高四位+BRR1+BRR2的第四位组成了UART_DIV*/
void uart_init()//115200@16Mhz，因为8266默认的波特率就是115200
{
    UART2_CR1=0x00;//1个起始位，8个数据位，无校验位
    UART2_CR2=0x2c;//接收中断使能，使能发送、接收
    UART2_CR3=0x00;//1个停止位
    //设置波特率近似115200
    UART2_BRR2=0x0B;
    UART2_BRR1=0x08;
}

/*******************************************************************************
 ****函数功能:UART2发送8位数据函数
 ****入口参数:
 ****出口参数:
 ****函数备注:
 *******************************************************************************/
void uart_send_byte(unsigned char Data)
{
    while((UART2_SR&0x80)==0);
    UART2_DR = Data;
}

void uart_convert_byte(unsigned char data)
{
    /* Convert \n to \r\n */
    if (data == '\n')
        uart_convert_byte('\r');

    uart_send_byte(data);
}

/*******************************************************************************
 ****函数名称:
 ****函数功能:发送Hex数据
 ****版本:V1.0
 ****日期:14-2-2014
 ****入口参数:dat-需要发送的数据
 ****出口参数:无
 ****说明:
 ********************************************************************************/
void uart_send_hex(unsigned char dat)
{
    uart_send_byte('0');
    uart_send_byte('x');
    uart_send_byte(hex_array[dat >> 4]);
    uart_send_byte(hex_array[dat & 0x0F]);
    uart_send_byte(' ');
}

/*******************************************************************************
 ****函数名称:
 ****函数功能:发送字符串
 ****版本:V1.0
 ****日期:14-2-2014
 ****入口参数:dat-需要发送的数据
 ****出口参数:无
 ****说明:
 ********************************************************************************/
void uart_send_string(unsigned char *dat)
{
    while (*dat != '\0')
    {
        uart_convert_byte(*dat);
        dat++;
    }
}

/*******************************************************************************
 ****函数功能:UART2接收数据函数
 ****入口参数:
 ****出口参数:
 ****函数备注:
 *******************************************************************************/
unsigned char uart_recv_byte(void)
{
    while((UART2_SR&0x20)==0);
    return ((unsigned char)UART2_DR);
}

