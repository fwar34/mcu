//https://www.cnblogs.com/lulipro/p/10815338.html
#include <reg52.h>
#include "dht11.h"
#include "delay.h"

#define DHT11_TIMEOUT -1
#define DHT11_READ_ERROR -2

sbit DHT11_DAT = P0 ^ 6;

unsigned char dht11_data[5]; //湿度十位，湿度个位，温度十位，温度个位，是否更新显示的标�?
unsigned char dht11_temp[5]; //湿度十位，湿度个位，温度十位，温度个位，校验�?

unsigned char dht11_check_sum()
{
    unsigned int check, sum;
    check = dht11_temp[4];
    sum = dht11_temp[0] + dht11_temp[1] + dht11_temp[2] + dht11_temp[3];
    if (check == sum)
        return 1;
    else
        return 0;
}

char dht11_read_data()
{
    unsigned char wait_cnt = 0;
    unsigned char i, j = 0;
    unsigned char bit_position = 0;

    /* 主机发送起始信�? */
    DHT11_DAT = 0; //主机将总线拉低（时�?>=18ms），使得DHT11能够接收到起始信�?
    Delay20ms();  //至少 18 ms
    DHT11_DAT = 1; // 主机将总线拉高（释放总线），代表起始信号结束�?
    Delay30us(); //延时20~40us

    /* 主机接收dht11响应信号ACK */
    while (!DHT11_DAT) { //DHT11将总线拉低至少80us，作为DHT11的响应信号（ACK�?
        Delay5us();
        ++wait_cnt;
        if (wait_cnt > 16)
            return DHT11_TIMEOUT;
    }

    wait_cnt = 0;
    while (DHT11_DAT) { //DHT11将总线拉高至少80us，为发送传感器数据做准备�?
        Delay5us();
        ++wait_cnt;
        if (wait_cnt > 16)
            return DHT11_TIMEOUT;
    }

    //主机接收dht11数据
    /* for (i = 0; i < 5 * 8; ++i) { */
    /*     wait_cnt = 0; */
    /*     while (!DHT11_DAT) { //拉低50us作为bit信号的起始标�? */
    /*         Delay5us(); */
    /*         ++wait_cnt; */
    /*         if (wait_cnt > 10) */
    /*             return DHT11_TIMEOUT; */
    /*     } */

    /*     wait_cnt = 0; */
    /*     while (DHT11_DAT) { //拉高。持�?26~28us表示bit0，持�?70us表示bit1 */
    /*         Delay5us(); */
    /*         ++wait_cnt; */
    /*         if (wait_cnt > 14) */
    /*             return DHT11_TIMEOUT; */
    /*     } */

    /*     if (wait_cnt > 6) { //说明是bit1 */
    /*         bit_position = 7 - i % 8; */
    /*         dht11_temp[i / 8] |= (unsigned char)(1 << bit_position); */
    /*     } */
    /* } */

    //主机接收dht11数据
    for (j = 0; j < 5; ++j) //dht每次返回5个字�?
    {
        for (i = 0; i < 8; ++i) //读每个字节的8�?
        {
            wait_cnt = 0;
            while (!DHT11_DAT) { //拉低50us作为bit信号的起始标�?
                Delay5us();
                ++wait_cnt;
                if (wait_cnt > 10)
                    return DHT11_TIMEOUT;
            }
            dht11_temp[j] <<= 1;   //从高位开始读，所以左�?

            wait_cnt = 0;
            while (DHT11_DAT) { //拉高。持�?26~28us表示0，持�?70us表示1
                Delay5us();
                ++wait_cnt;
                if (wait_cnt > 14)
                    return DHT11_TIMEOUT;
            }

            if (wait_cnt > 6) { //高电平大�?30us，说明是1
                dht11_temp[j] |= 0x01;
            } else {
                dht11_temp[j] &= 0xFE;
            }
        }
    }

    if (dht11_check_sum()) {
        for (i = 0; i < 4; ++i) {
            dht11_data[i] = dht11_temp[i];
        }
    } else {
        return DHT11_READ_ERROR;
    }

    return 0;
}

void dht11_read_data2()
{
    unsigned char high_count = 0;
    unsigned char i, j = 0;

    /* UART_send_string("read dht11\n"); */
    
    /* 主机发送起始信�? */
    TR1 = 0;
    TH1 = 0;
    TL1 = 0;
    DHT11_DAT = 0; //主机将总线拉低（时�?>=18ms），使得DHT11能够接收到起始信�?
    TR1 = 1; //开启timer1
    while (TH1 * 256 + TL1 <= 18433); //18433 × 1.085 = 20ms
    /* Delay20ms();  //至少 18 ms */
    TR1 = 0;

    TH1 = 0;
    TL1 = 0;
    DHT11_DAT = 1; // 主机将总线拉高（释放总线），代表起始信号结束�?
    TR1 = 1;
    while (TH1 * 256 + TL1 <= 27); //27 × 1.085 = 30us
    /* Delay30us(); //延时20~40us */
    TR1 = 0;

    TH1 = 0;
    TL1 = 0;
    TR1 = 1;
    /* 主机接收dht11响应信号ACK */
    while (!DHT11_DAT) { //DHT11将总线拉低至少80us，作为DHT11的响应信号（ACK�?
        if (TH1 * 256 + TL1 > 73) { //73 × 1.085 = 80us
            /* UART_send_string("error1"); */
            return;
        }
    }
    TR1 = 0;

    TH1 = 0;
    TL1 = 0;
    TR1 = 1;
    while (DHT11_DAT) { //DHT11将总线拉高至少80us，为发送传感器数据做准备�?
        if (TH1 * 256 + TL1 > 73) { //73 × 1.085 = 80us
            /* UART_send_string("error2"); */
            return;
        }
    }
    TR1 = 0;

    //主机接收dht11数据
    for (j = 0; j < 5; ++j) //dht每次返回5个字�?
    {
        for (i = 0; i < 8; ++i) //读每个字节的8�?
        {
            TH1 = 0;
            TL1 = 0;
            TR1 = 1;
            while (!DHT11_DAT) { //拉低50us作为bit信号的起始标�?
                if (TH1 * 256 + TL1 > 46) { //46 × 1.085 = 50us
                    /* UART_send_string("error3"); */
                    return;
                }
            }
            TR1 = 0;
            dht11_temp[j] <<= 1;   //从高位开始读，所以左�?

            TH1 = 0;
            TL1 = 0;
            TR1 = 1;
            while (DHT11_DAT) { //拉高。持�?26~28us表示0，持�?70us表示1
                high_count = TH1 * 256 + TL1;
                if (high_count > 64) { //64 × 1.085 = 70us
                    /* UART_send_string("error4"); */
                    return;
                }
            }
            TR1 = 0;

            if (high_count > 27) { //高电平大�?30us，说明是1, 27 × 1.085 = 30us
                dht11_temp[j] |= 0x01;
            } else {
                dht11_temp[j] &= 0xFE;
            }
        }
    }

    // if (dht11_check_sum()) {
    //     for (i = 0; i < 4; ++i) {
    //         dht11_data[i] = dht11_temp[i];
    //     }
    //     dht11_data[4] = 1;
    // }

        for (i = 0; i < 4; ++i) {
            dht11_data[i] = dht11_temp[i];
        }
        dht11_data[4] = 1;
}
