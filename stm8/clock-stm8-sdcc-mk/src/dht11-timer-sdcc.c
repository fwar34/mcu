//https://pdf1.alldatasheet.com/datasheet-pdf/view/1132088/ETC2/DHT11.html
#include "stm8s.h"
#include "uart_sdcc.h"
#include "dht11.sdcc.h"

#define DHT11_TIMEOUT -1
#define DHT11_READ_ERROR -2

#define DHT11_DAT_PIN GPIO_PIN_4
#define DHT11_DAT_PORT GPIOF

#define DHT11_CLR() GPIO_WriteLow(DHT11_DAT_PORT, DHT11_DAT_PIN)
#define DHT11_SET() GPIO_WriteHigh(DHT11_DAT_PORT, DHT11_DAT_PIN)

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

    /* uart_send_string("read dht11\n"); */
    
    /* 主机发送起始信号 */
    GPIO_Init(DHT11_DAT_PORT, DHT11_DAT_PIN, GPIO_MODE_OUT_PP_LOW_FAST);
    TIM2_SetCounter(0x0000);
    DHT11_CLR(); //主机将总线拉低（时间>=18ms），使得DHT11能够接收到起始信号
    TIM2_Cmd(ENABLE); //开启timer1
    
    while (TIM2_GetCounter() <= 20000); //20ms
    /* Delay20ms();  //至少 18 ms */

    DHT11_SET(); // 主机将总线拉高（释放总线），代表起始信号结束。
    TIM2_SetCounter(0x0000);
    while (TIM2_GetCounter() <= 30); //30us
    /* Delay30us(); //延时20~40us */

    TIM2_SetCounter(0x0000);
    GPIO_Init(DHT11_DAT_PORT, DHT11_DAT_PIN, GPIO_MODE_IN_PU_NO_IT);
    /* 主机接收dht11响应信号ACK */
    while (!GPIO_ReadInputPin(DHT11_DAT_PORT, DHT11_DAT_PIN)) { //DHT11将总线拉低至少80us，作为DHT11的响应信号（ACK）
        if (TIM2_GetCounter() > 93) { //93us
            uart_send_string("dht11 error1");
            TIM2_Cmd(DISABLE);
            return;
        }
    }

    TIM2_SetCounter(0x0000);
    while (GPIO_ReadInputPin(DHT11_DAT_PORT, DHT11_DAT_PIN)) { //DHT11将总线拉高至少80us，为发送传感器数据做准备。
        if (TIM2_GetCounter() > 98) { //98us
            uart_send_string("dht11 error2");
            TIM2_Cmd(DISABLE);
            return;
        }
    }

    //主机接收dht11数据
    for (j = 0; j < 5; ++j) //dht每次返回5个字节
    {
        for (i = 0; i < 8; ++i) //读每个字节的8位
        {
            TIM2_SetCounter(0x0000);
            while (!GPIO_ReadInputPin(DHT11_DAT_PORT, DHT11_DAT_PIN)) { //拉低54us作为bit信号的起始标志
                if (TIM2_GetCounter() > 60) { //60 × 1.085 = 65us
                    uart_send_string("dht11 error3");
                    TIM2_Cmd(DISABLE);
                    return;
                }
            }
            dht11_temp[j] <<= 1;   //从高位开始读，所以左移

            TIM2_SetCounter(0x0000);
            while (GPIO_ReadInputPin(DHT11_DAT_PORT, DHT11_DAT_PIN)) { //拉高。持续26~28us表示0，持续70us表示1
                if (TIM2_GetCounter() > 64) { //64 × 1.085 = 70us
                    uart_send_string("dht11 error4");
                    TIM2_Cmd(DISABLE);
                    return;
                }
            }
            TIM2_Cmd(DISABLE);
            high_count = TIM2_GetCounter();
            TIM2_Cmd(ENABLE);

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
    TIM2_Cmd(DISABLE);
}
