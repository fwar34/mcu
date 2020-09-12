#ifndef _DS1302_H
#define _DS1302_H 

#include "common.h"

void ds1302_init();
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
