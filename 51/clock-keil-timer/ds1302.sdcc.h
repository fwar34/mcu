#ifndef _DS1302_H
#define _DS1302_H

#include "common.sdcc.h"

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

void ds1302_init();
unsigned char ds1302_read(unsigned char address);
void ds1302_read_time(DS1302_TIME* time);
void ds1302_write_time(DS1302_TIME* time);
void ds1302_write_ram(unsigned char ram_num, unsigned char dat);
unsigned char ds1302_read_ram(unsigned char ram_num);
unsigned char ds1302_is_running();
char process_time_settings(unsigned char row, unsigned char column);
void enter_settings();
void exit_settings();
void ds1302_pause(bit flag);

#endif
