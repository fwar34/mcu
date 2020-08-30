#include <reg52.h>
#include "dht11.h"
#include "delay.h"

sbit DHT11_DAT = P2 ^ 6;

unsigned dht11_data[5]; //湿度十位，湿度个位，温度十位，温度个位，校验值

unsigned char dht11_start()
{
    DHT11_DAT = 0; //主机把总线拉低
    Delay20ms();  //主机把总线拉低至少18ms，以保证DHT11可以检测到起始信号
    DHT11_DAT = 1;  //主机释放总线(主机拉高总线)
    Delay30us(); //主机将总线拉高20-40us
    while (!DHT11_DAT); //dht11响应的时候先是拉低dat 80us
    while (DHT11_DAT);  //在拉高dat 80us
    return 1;
}

void dht11_read_data()
{
    unsigned char i, j;
    dht11_start();
    for (j = 0; j < 5; ++j) //dht每次返回5个字节
    {
        for (i = 0; i < 8; ++i) //读每个字节的8位
        {
            while (!DHT11_DAT); //每一bit都以50us的低电平开始
            dht11_data[j] <<= 1;   //从高位开始读，所以左移
            Delay50us(); //延时50us后，再次判断DATA_INPUT的值
            if (DHT11_DAT)
            {
                dht11_data[j] |= 0x01;
                while (DHT11_DAT);  //将此bit读完
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
