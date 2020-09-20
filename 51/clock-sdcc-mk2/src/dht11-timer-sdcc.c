//https://pdf1.alldatasheet.com/datasheet-pdf/view/1132088/ETC2/DHT11.html
#include <mcs51/8051.h>
#include "uart_sdcc.h"
#include "dht11.sdcc.h"

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
    unsigned char high_count = 0;
    unsigned char i, j = 0;

    /* UART_send_string("read dht11\n"); */
    
    /* 主机发送起始信号 */
    TH1 = 0;
    TL1 = 0;
    DHT11_DAT = 0; //主机将总线拉低（时间>=18ms），使得DHT11能够接收到起始信号
    TR1 = 1; //开启timer1
    while (TH1 * 256 + TL1 <= 18433); //18433 × 1.085 = 20ms
    /* Delay20ms();  //至少 18 ms */

    DHT11_DAT = 1; // 主机将总线拉高（释放总线），代表起始信号结束。
    TH1 = 0;
    TL1 = 0;
    while (TH1 * 256 + TL1 <= 27); //27 × 1.085 = 30us
    /* Delay30us(); //延时20~40us */

    TH1 = 0;
    TL1 = 0;
    /* 主机接收dht11响应信号ACK */
    while (!DHT11_DAT) { //DHT11将总线拉低至少80us，作为DHT11的响应信号（ACK）
        if (TH1 * 256 + TL1 > 85) { //85 × 1.085 = 92.2us
            UART_send_string("error1");
            TR1 = 0;
            return;
        }
    }

    TH1 = 0;
    TL1 = 0;
    while (DHT11_DAT) { //DHT11将总线拉高至少80us，为发送传感器数据做准备。
        if (TH1 * 256 + TL1 > 95) { //90 × 1.085 = 97.65us
            UART_send_string("error2");
            TR1 = 0;
            return;
        }
    }
    /* TR1 = 0; */
    /* UART_send_byte(0xAA); */
    /* UART_send_byte(TH1); */
    /* UART_send_byte(0xBB); */
    /* UART_send_byte(TL1); */

    //主机接收dht11数据
    for (j = 0; j < 5; ++j) //dht每次返回5个字节
    {
        for (i = 0; i < 8; ++i) //读每个字节的8位
        {
            TH1 = 0;
            TL1 = 0;
            while (!DHT11_DAT) { //拉低54us作为bit信号的起始标志
                if (TH1 * 256 + TL1 > 60) { //60 × 1.085 = 65us
                    UART_send_string("error3");
                    TR1 = 0;
                    return;
                }
            }
            dht11_temp[j] <<= 1;   //从高位开始读，所以左移

            TH1 = 0;
            TL1 = 0;
            while (DHT11_DAT) { //拉高。持续26~28us表示0，持续70us表示1
                if (TH1 * 256 + TL1 > 80) { //80 × 1.085 = 70us
                    UART_send_string("error4");
                    TR1 = 0;
                    return;
                }
            }
            TR1 = 0;
            high_count = TH1 * 256 + TL1;
            TR1 = 1;

            if (high_count > 35) { //高电平大于37.9us，说明是1, 35 × 1.085 = 37.9us
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
    TR1 = 0;
}
