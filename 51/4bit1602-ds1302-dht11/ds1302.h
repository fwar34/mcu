#ifndef _DS1302_H
#define _DS1302_H

extern unsigned char current_setting;

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
void ds1302_read_time(DS1302_TIME* time);
void ds1302_write_time(DS1302_TIME* time);
void ds1302_write_ram(unsigned char ram_num, unsigned char dat);
unsigned char ds1302_read_ram(unsigned char ram_num);
unsigned char ds1302_is_running();
char process_time_settings(unsigned char row, unsigned char column);

#endif
