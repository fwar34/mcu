#include <mcs51/8051.h>
#include "key.sdcc.h"
#include "ds1302.sdcc.h"
#include "delay.sdcc.h"

#define key1 P3_4
#define key2 P3_5
#define key3 P3_6
#define key4 P3_7

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
