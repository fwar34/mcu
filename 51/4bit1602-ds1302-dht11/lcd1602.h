#ifndef _LCD_1602_H_
#define _LCD_1602_H_

void initLcd1602();
void display(DS1302_TIME* time);
void write_str(unsigned char addr_start, unsigned char* str);
void write_char(unsigned char x, unsigned char y, unsigned char dat);

#endif
