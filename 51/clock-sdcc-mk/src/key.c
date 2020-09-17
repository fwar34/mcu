#include <reg52.h>
#include "key.h"
#include "ds1302.h"
#include "delay.h"

//只能使用第一列的两个按键，因为P37为低电平的话蜂鸣器就会响，第一次画pcb出的问题。。
sbit key1 = P3 ^ 4;
sbit key2 = P3 ^ 5;
sbit key3 = P3 ^ 6;
sbit key4 = P3 ^ 7;

unsigned char row = 0;
unsigned char column = 0;

void key_scan()
{
}

char process_key()
{
    char ret = -1;
    key_scan();
    /* if (row && column) */
    /*     ret = process_time_settings(row, column); */
    /* row = 0; */
    /* column = 0; */

    return ret;
}
