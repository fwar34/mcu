#include <reg52.h>
#include "key.h"
#include "ds1302.h"
#include "delay.h"

//只能使用第一列的两个按键，因为P37为低电平的话蜂鸣器就会响，第一次画pcb出的问题。。
sbit row1 = P3 ^ 4;
sbit row2 = P3 ^ 5;
sbit column1 = P3 ^ 6;
/* sbit column2 = P3 ^ 7; */

unsigned char row;
unsigned char column;

void key_scan()
{
    row1 = 0;
    row2 = 0;
    column1 = 1;
    if (column1 == 0) { //检测1列中的哪一列被按下
        Delay50ms(); //延时去抖
        if (column1 == 0) {
            column = 1;
        }
    }

    row1 = 1;
    row2 = 1;
    column1 = 0;
    if (row1 == 0 || row2 == 0) {   //检测2行中的哪一行被按下
        Delay50ms(); //延时去抖
        if (row1 == 0) {
            row = 1;
        } else if (row2 == 0) {
            row = 2;
        }   
    }
}

char process_key()
{
    char ret = -1;
    key_scan();
    if (row && column)
        ret = process_time_settings(row, column);
    row = 0;
    column = 0;

    return ret;
}
