#ifndef _LCD_1602_H_
#define _LCD_1602_H_

#include "common.h"

void initLcd1602();
void display(DS1302_TIME* time);
void write_str(unsigned char addr_start, unsigned char* str);
void write_char(unsigned char x, unsigned char y, unsigned char dat);
void display_dht11();
void flicker_year(unsigned char x);
void flicker_month(unsigned char x);
void flicker_day(unsigned char x);
void flicker_week(unsigned char x);
void flicker_hour(unsigned char x);
void flicker_minute(unsigned char x);

#endif
