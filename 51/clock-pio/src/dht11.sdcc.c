#include <mcs51/8051.h>
#include "dht11.sdcc.h"
#include "delay.sdcc.h"
#include "uart_sdcc.h"

#define DHT11_TIMEOUT -1
#define DHT11_READ_ERROR -2

/* __sbit __at (P0 + 6) DHT11_DAT; */
#define DHT11_DAT P0_6

unsigned char dht11_data[5]; //湿度十位，湿度个位，温度十位，温度个位，是否更新显示的标志
unsigned char dht11_temp[5]; //湿度十位，湿度个位，温度十位，温度个位，校验值


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

void dht11_read_data()
{
    unsigned char uart_count = 0;
    unsigned char wait_cnt = 0;
    unsigned char i, j = 0;
    unsigned char bit_position = 0;

    UART_send_string("read dht11\n");
    /* 主机发送起始信号 */
    DHT11_DAT = 0; //主机将总线拉低（时间>=18ms），使得DHT11能够接收到起始信号
    Delay20ms();  //至少 18 ms
    DHT11_DAT = 1; // 主机将总线拉高（释放总线），代表起始信号结束。
    Delay30us(); //延时20~40us

    /* 主机接收dht11响应信号ACK */
    while (!DHT11_DAT) { //DHT11将总线拉低至少80us，作为DHT11的响应信号（ACK）
        Delay5us();
        ++wait_cnt;
        if (wait_cnt > 16) {
            UART_send_string("error1");
            return;
        }
    }

    wait_cnt = 0;
    while (DHT11_DAT) { //DHT11将总线拉高至少80us，为发送传感器数据做准备。
        Delay5us();
        ++wait_cnt;
        if (wait_cnt > 16) {
            UART_send_string("error2");
            return;
        }
    }

    //主æº接收dht11数据
    /* for (i = 0; i < 5 * 8; ++i) { */
    /*     wait_cnt = 0; */
    /*     while (!DHT11_DAT) { //拉低50us作为bit信号的起始标志 */
    /*         Delay5us(); */
    /*         ++wait_cnt; */
    /*         if (wait_cnt > 10) */
    /*             return DHT11_TIMEOUT; */
    /*     } */

    /*     wait_cnt = 0; */
    /*     while (DHT11_DAT) { //拉高。持续26~28us表示bit0，持续70us表示bit1 */
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
    for (j = 0; j < 5; ++j) //dht每次返回5个字节
    {
        for (i = 0; i < 8; ++i) //读每个字节的8位
        {
            wait_cnt = 0;
            while (!DHT11_DAT) { //拉ä½50us作为bit信号的起始标志
                Delay5us();
                ++wait_cnt;
                if (wait_cnt > 10) {
                    UART_send_string("error3");
                    return;
                }
            }
            dht11_temp[j] <<= 1;   //从高位开始读，所以左移

            wait_cnt = 0;
            while (DHT11_DAT) { //拉高。持续26~28us表示0，持续70us表示1
                Delay5us();
                ++wait_cnt;
                if (wait_cnt > 14) {
                    UART_send_string("error4");
                    return;
                }
            }

            if (wait_cnt > 6) { //高电平大于30us，说明是1
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
        dht11_data[4] = 1;
    }
}

