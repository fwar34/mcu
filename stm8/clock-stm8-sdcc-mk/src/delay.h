//支持不同时钟频率
//提供delay_us,delay_ms两个延时函数.

#ifndef _DELAY_H
#define _DELAY_H

void delay_init(unsigned char clk);//延时函数初始化
void delay_us(unsigned short nus); //us级延时函数,最大65536us.
void delay_ms(unsigned long nms); //ms级延时函数

#endif
