#include <reg52.h>
#include "key.h"
#include "ds1302.h"

sbit row1 = P3 ^ 4;
sbit row2 = P3 ^ 5;
sbit column1 = P3 ^ 6;
sbit column2 = P3 ^ 7;

unsigned char row;
unsigned char column;

void delay(unsigned short count)
{
    while (count--);
}

void key_scan()
{
    char a;
    row1 = 0;
    row2 = 0;
    column1 = 1;
    column2 = 1;
    if (column1 == 0 || column2 == 0) { //检测2列中的哪一列被按下
        delay(1000); //延时去抖
        if (column1 == 0) {
            column = 1;
        } else if (column2 == 0) {
            column = 2;
        }
    }

    row1 = 1;
    row2 = 1;
    column1 = 0;
    column2 = 0;
    if (row1 == 0 || row2 == 0) {   //检测2行中的哪一行被按下
        delay(1000); //延时去抖
        if (row1 == 0) {
            row = 1;
        } else if (row2 == 0) {
            row = 2;
        }   
    }

    while (a < 50 && row1 && row2) { //延时，确保没有按键再按下
        a++;
        delay(1000);
    }
}

char process_key()
{
    char ret = -1;
    key_scan();
    if (row && column)
        ret = process_time_settings();
    row = 0;
    column = 0;

    return ret;
}
