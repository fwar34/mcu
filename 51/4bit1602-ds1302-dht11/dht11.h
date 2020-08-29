#ifndef _DHT_11_H_
#define _DHT_11_H_

#include "delay.h"

#define DHT11_DAT_IN PB_IDR_IDR4
#define DHT11_DAT_OUT PB_ODR_ODR4

unsigned char dht11_data[5]; //湿度十位，湿度个位，温度十位，温度个位，校验值

void dat_write()
{
    /*PA_DDR |= (0x1 << 4);
    PA_CR1 |= (0x1 << 4);
    PA_CR2 |= (0x1 << 4);*/
    PA_DDR_DDR3 = 1;
    PA_CR1_C13 = 1;
    PA_CR2_C23 = 1;
    
}

void dat_read()
{
    /*PA_DDR &= ~(0x1 << 4);
    PA_CR1 &= ~(0x1 << 4);
    PA_CR2 &= ~(0x1 << 4);*/
    PB_DDR_DDR4 = 0;
    PB_CR1_C14 = 1;
    PB_CR2_C24 = 0;
}

unsigned char dht11_start()
{
    dat_write();
    DHT11_DAT_OUT = 0; //主机把总线拉低
    delay_ms(20);  //主机把总线拉低至少18ms，以保证DHT11可以检测到起始信号
    DHT11_DAT_OUT = 1;  //主机释放总线(主机拉高总线)
    dat_read();
    delay_us(30); //主机将总线拉高20-40us
    while (!DHT11_DAT_IN); //dht11响应的时候先是拉低dat 80us
    while (DHT11_DAT_IN);  //在拉高dat 80us
    return 1;
}

void dht11_read_data()
{
    unsigned char i, j;
    for (j = 0; j < 5; ++j) //dht每次返回5个字节
    {
        for (i = 0; i < 8; ++i) //读每个字节的8位
        {
            while (!DHT11_DAT_IN); //每一bit都以50us的低电平开始
            dht11_data[j] <<= 1;   //从高位开始读，所以左移
            delay_us(50); //延时50us后，再次判断DATA_INPUT的值
            if (DHT11_DAT_IN)
            {
                dht11_data[j] |= 0x01;
                while (DHT11_DAT_IN);  //将此bit读完
            }
            else
            {
                dht11_data[j] &= 0xFE;
            }
        }
    }
}

unsigned char dht11_check_sum()
{
    unsigned int check, sum;
    check = dht11_data[4];
    sum = dht11_data[0] + dht11_data[1] + dht11_data[2] + dht11_data[3];
    if (check == sum)
        return 1;
    else
        return 0;
}

#endif
