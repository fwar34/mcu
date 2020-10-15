#include "iostm8.h"
#include "key.sdcc.h"
#include "ds1302.sdcc.h"

#define KEY1_PIN PB_IDR_IDR2
#define KEY2_PIN PB_IDR_IDR3
#define KEY3_PIN PD_IDR_IDR7
#define KEY4_PIN PA_IDR_IDR1

unsigned char row = 0;
unsigned char column = 0;

void key_init()
{
    //sw
    PB_DDR &= ~(MASK_PB_DDR_DDR3);
    PB_CR1 |= MASK_PB_CR1_C13;
    PB_CR2 |= MASK_PB_CR2_C23;

    //sw
    PD_DDR_DDR7 = 0;
    PD_CR1_C17 = 1;
    PD_CR2_C27 = 1;

    //sw
    PA_DDR_DDR1 = 0;
    PA_CR1_C11 = 1;
    PA_CR2_C21 = 1;
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
