#include <stc8.h>
#include "key.sdcc.h"
#include "ds1302.sdcc.h"
#include "delay.sdcc.h"

sbit key1 = P3 ^ 4;
sbit key2 = P3 ^ 5;
sbit key3 = P3 ^ 6;
sbit key4 = P3 ^ 7;

unsigned char row = 0;
unsigned char column = 0;

void key_scan()
{
}

unsigned char process_key()
{
    char ret = 0;
    key_scan();
    /* if (row && column) */
    /*     ret = process_time_settings(row, column); */
    /* row = 0; */
    /* column = 0; */

    return ret;
}
