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
    UART2_DeInit();
    /*
    115200:传输速度
    UART2_WORDLENGTH_8D:字长8位
    UART2_STOPBITS_1:一个停止位
    UART2_PARITY_NO:没有校验位
    UART2_MODE_TXRX_ENABLE:收发使能
    */
    UART2_Init(115200, UART2_WORDLENGTH_8D, UART2_STOPBITS_1, UART2_PARITY_NO, UART2_SYNCMODE_CLOCK_DISABLE, UART2_MODE_TXRX_ENABLE);
    UART2_ITConfig(UART2_IT_RXNE_OR, ENABLE);//使能接收中断
    UART2_Cmd(ENABLE);//使能UART3
}

/*******************************************************************************
 ****函数名称:
 ****函数功能:发送8位数据
 ****版本:V1.0
 ****日期:14-2-2014
 ****入口参数:dat-需要发送的数据
 ****出口参数:无
 ****说明:
 ********************************************************************************/
void uart_send_byte(u8 dat)
{
    while ((UART2_GetFlagStatus(UART2_FLAG_TXE) == RESET));
    UART2_SendData8(dat);
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
    uart_send_byte('0' + dat >> 4);
    uart_send_byte('0' + dat & 0x0F);
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
        uart_send_byte(*dat);
        dat++;
    }
}
