#ifndef DS1302_H
#define DS1302_H

#include "iostm8s105c6.h"

//#define DS1302_RST_PIN PC_ODR_ODR6
//#define DS1302_IO_PIN_IN PC_IDR_IDR5
//#define DS1302_IO_PIN_OUT PC_ODR_ODR5
//#define DS1302_CLK_PIN PC_ODR_ODR4

#define DS1302_RST_PIN PB_ODR_ODR2
#define DS1302_IO_PIN_IN PB_IDR_IDR1
#define DS1302_IO_PIN_OUT PB_ODR_ODR1
#define DS1302_CLK_PIN PB_ODR_ODR0

#define DS1302_SEC_REG 0x80
#define DS1302_MIN_REG 0x82
#define DS1302_HR_REG 0x84
#define DS1302_DATE_REG 0x86
#define DS1302_MONTH_REG 0x88
#define DS1302_DAY_REG 0x8a
#define DS1302_YEAR_REG 0x8c
#define DS1302_CONTROL_REG 0x8e
#define DS1302_CHARGER_REG 0x90
#define DS1302_CLKBURST_REG 0xbe
#define DS1302_RAM_REG 0xc0

typedef struct _DS1302_TIME
{
    unsigned char year;
    unsigned char month;
    unsigned char day;
    unsigned char week;
    unsigned char hour;
    unsigned char minute;
    unsigned char second;
} DS1302_TIME;

void ds1302_init();
unsigned char ds1302_is_running();
unsigned char ds1302_check();
void ds1302_write_time(DS1302_TIME* time);
void ds1302_read_time(DS1302_TIME* time);
void ds1302_write_ram(unsigned char ram_num,unsigned char dat);
unsigned char  ds1302_read_ram(unsigned char ram_num);

#endif
