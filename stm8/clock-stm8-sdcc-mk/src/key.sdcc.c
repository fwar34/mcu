#include "stm8s.h"
#include "key.sdcc.h"
#include "ds1302.sdcc.h"
#include "delay.sdcc.h"

#define KEY1_PORT GPIOB
#define KEY1_PIN GPIO_PIN_2
#define KEY2_PORT GPIOB
#define KEY2_PIN GPIO_PIN_3
#define KEY3_PORT GPIOD
#define KEY3_PIN GPIO_PIN_7
#define KEY4_PORT GPIOA
#define KEY4_PIN GPIO_PIN_1

unsigned char row = 0;
unsigned char column = 0;

void key_init()
{
    GPIO_Init(KEY1_PORT, KEY1_PIN, GPIO_MODE_IN_PU_IT);
    GPIO_Init(KEY2_PORT, KEY2_PIN, GPIO_MODE_IN_PU_IT);
    GPIO_Init(KEY3_PORT, KEY3_PIN, GPIO_MODE_IN_PU_IT);
    GPIO_Init(KEY4_PORT, KEY4_PIN, GPIO_MODE_IN_PU_IT);
}

void key_scan()
{
}

unsigned char process_key()
{
    char ret = 0;
    key_scan();
    if (row && column)
        ret = process_time_settings(row, column);
    row = 0;
    column = 0;

    return ret;
}
