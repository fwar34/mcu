#include <reg52.h>
#include <intrins.h>
#include "ds1302.h"

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

sbit DS1302_RST = P1 ^ 2;
sbit DS1302_IO = P1 ^ 1;
sbit DS1302_CLK = P1 ^ 0;

//current_setting可以作为下标来取，秒不用设置，所以不在数组里面
unsigned char ds1302_reg_addr[] = {0, 0x82, 0x84, 0x86, 0x88, 0x8a, 0x8c, 0x8e, 0x90, 0xbe, 0xc0};

unsigned char current_setting;

//sbit DS1302_RST = P2 ^ 7;
//sbit DS1302_IO = P1 ^ 2;
//sbit DS1302_CLK = P1 ^ 7;

void ds1302_init()
{
    DS1302_RST = 0;
    DS1302_CLK = 0;
}

void ds1302_write_byte(unsigned char dat) 
{
    unsigned char i;
    for (i = 0; i < 8; i++) {
        DS1302_CLK = 0;
        if (dat & 0x01) {
            DS1302_IO = 1;
        } else {
            DS1302_IO = 0;
        }           
        DS1302_CLK = 1;
        dat >>= 1; 
    }
}  

unsigned char ds1302_read_byte()
{
    unsigned char i,ret=0;
    for (i = 0; i < 8; i++) {
        DS1302_CLK = 0;
        ret >>= 1;
        if (DS1302_IO) {
            ret |= 0x80;
        }
        DS1302_CLK = 1;
    } 
    return ret;
} 

void ds1302_write(unsigned char address, unsigned char dat)     
{
    DS1302_RST = 0;
    DS1302_CLK = 0;
    DS1302_RST = 1;
    ds1302_write_byte(address);
    ds1302_write_byte(dat);
    DS1302_RST = 0;
}

/****************************************************************************/
unsigned char ds1302_read(unsigned char address)
{
    unsigned char ret;
    DS1302_RST = 0;
    DS1302_CLK = 0;
    DS1302_RST = 1;
    ds1302_write_byte(address | 0x01);   //读最低位是1
    ret = ds1302_read_byte();
    DS1302_RST = 0;
    return ret;
}

unsigned char ds1302_check() 
{ 
    unsigned char ret;
    ds1302_write(DS1302_CONTROL_REG, 0x80); 
    ret = ds1302_read(DS1302_CONTROL_REG);
    if (ret == 0x80)
        return 1; 
    return 0; 
}

unsigned char ds1302_is_running()
{
    unsigned char ret = ds1302_read(DS1302_SEC_REG);
    if (ret & 0x80)
        return 0; 
    return 1; 
}

void ds1302_read_time(DS1302_TIME* time) 
{ 
    time->year = ds1302_read(DS1302_YEAR_REG);
    time->month = ds1302_read(DS1302_MONTH_REG);
    time->day = ds1302_read(DS1302_DATE_REG);
    time->week = ds1302_read(DS1302_DAY_REG);
    time->hour = ds1302_read(DS1302_HR_REG);
    time->minute = ds1302_read(DS1302_MIN_REG);
    time->second = ds1302_read(DS1302_SEC_REG);
}

//转换成bcd
void ds1302_write_convert(unsigned char addr, unsigned char dat)
{
    ds1302_write(addr, (dat / 10) << 4 | dat % 10);
}

void ds1302_write_time(DS1302_TIME* time) 
{ 
    ds1302_write(DS1302_CONTROL_REG, 0x00);
    ds1302_write(DS1302_SEC_REG, 0x80);
    ds1302_write(DS1302_CHARGER_REG, 0x00); //禁止充电
    ds1302_write_convert(DS1302_YEAR_REG, time->year);
    ds1302_write_convert(DS1302_MONTH_REG, time->month);
    ds1302_write_convert(DS1302_DATE_REG, time->day);
    ds1302_write_convert(DS1302_DAY_REG, time->week);
    ds1302_write_convert(DS1302_HR_REG, time->hour);
    ds1302_write_convert(DS1302_MIN_REG, time->minute);
    ds1302_write_convert(DS1302_SEC_REG, time->second);
    ds1302_write(DS1302_CONTROL_REG, 0x80); 
}

void ds1302_write_ram(unsigned char ram_num,unsigned char dat) 
{ 
    ds1302_write(DS1302_CONTROL_REG, 0x00); 
    ds1302_write((DS1302_RAM_REG | (ram_num << 2)), dat);
    ds1302_write(DS1302_CONTROL_REG, 0x80);
}

unsigned char ds1302_read_ram(unsigned char ram_num) 
{ 
    unsigned char ret;
    ret = ds1302_read((DS1302_RAM_REG | (ram_num << 2)));
    return ret;
}

char process_time_settings(unsigned char row, unsigned char column)
{
    if (row == 1 && column == 1) { //key1 切换设置项
        current_setting++;
    } else if (row == 1 && column == 2) { //key2 确认
        confirm();
    } else if (row == 2 && column == 1) { //key3 加
        plus();
    } else if (row == 2 && column == 2) { //key4 减
        minus();
    } else {
        return -1; //返回非0表示没有按键按下
    }

    return 0;
}
