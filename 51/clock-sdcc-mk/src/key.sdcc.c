#include <8051.h>
#include "key.sdcc.h"
#include "ds1302.sdcc.h"
#include "delay.sdcc.h"

__sbit __at (P3+4) key1;
__sbit __at (P3+5) key2;
__sbit __at (P3+6) key3;
__sbit __at (P3+7) key4;

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
