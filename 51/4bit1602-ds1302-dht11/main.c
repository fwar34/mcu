#include <reg52.h>
#include "ds1302.h"
#include "lcd1602.h"

void display_sec(unsigned char x)
{
    unsigned char i, j;
    i = x / 10; //取十位
    j = x % 10; //取个位
    write_char(1, 6, i + '0');
    write_char(1, 7, j + '0');
}

void display_min(unsigned char x)
{
    unsigned char i, j;
    i = x / 10; //取十位
    j = x % 10; //取个位
    write_char(1, 3, i + '0');
    write_char(1, 4, j + '0');
}

void display_hour(unsigned char x)
{
    unsigned char i, j;
    i = x / 10; //取十位
    j = x % 10; //取个位
    write_char(1, 0, i + '0');
    write_char(1, 1, j + '0');
}

void display_day(unsigned char x)
{
    unsigned char i, j;
    i = x / 10; //取十位
    j = x % 10; //取个位
    write_char(0, 8, i + '0');
    write_char(0, 9, j + '0');
}

void display_month(unsigned char x)
{
    unsigned char i, j;
    i = x / 10; //取十位
    j = x % 10; //取个位
    write_char(0, 5, i + '0');
    write_char(0, 6, j + '0');
}

void display_year(unsigned char x)
{
    unsigned char i, j;
    i = x / 10; //取十位
    j = x % 10; //取个位
    write_char(0, 2, i + '0');
    write_char(0, 3, j + '0');
}
void display_week(unsigned char x)
{
    unsigned char i, j;
    i = x / 10; //取十位
    j = x % 10; //取个位
    write_char(0, 11, i + '0');
    write_char(0, 12, j + '0');
}

//秒，分，时，日，月，星期，年
void display(DS1302_TIME* time)
{
    write_char(0, 0, '2');
    write_char(0, 1, '0');
    write_char(0, 4, '-');
    write_char(0, 7, '-');
    write_char(0, 10, '|');
    write_char(1, 2, ':');
    write_char(1, 5, ':');

    display_sec(((time->second & 0x70) >> 4) * 10 + (time->second & 0x0F));
    display_min(((time->minute & 0x70) >> 4) * 10 + (time->minute & 0x0F));
    display_hour(((time->hour & 0x30) >> 4) * 10 + (time->hour & 0x0F));
    display_day(((time->day & 0x30) >> 4) * 10 + (time->day & 0x0F));
    display_month(((time->month & 0x10) >> 4) * 10 + (time->month & 0x0F));
    display_week(time->week & 0x07);
    display_year((time->year >> 4) * 10 + (time->year & 0x0F));
}

/*void display_dht11()*/
/*{*/
    /*unsigned char i, j;*/
    /*i = dht11_data[0] / 10; //湿度十位*/
    /*j = dht11_data[0] % 10; //湿度个位*/
    /*write_char(1, 9, i + '0');*/
    /*write_char(1, 10, j + '0');*/
    
    /*i = dht11_data[2] / 10; //温度十位*/
    /*j = dht11_data[2] % 10; //温度个位*/
    /*write_char(1, 12, i + '0');*/
    /*write_char(1, 13, j + '0');*/
/*}*/

void main(void)
{
    //初始时间20年8月16号14点16分55秒星期天 
    DS1302_TIME start_time = {20, 8, 18, 2, 22, 19, 40};
    DS1302_TIME current_time;
    initLcd1602();

    if (!ds1302_is_running()) {
        ds1302_write_time(&start_time);
    }

    while (1)
    {
        ds1302_read_time(&current_time);
        display(&current_time);
        /*dht11_start();*/
        /*display_dht11();*/
        /*uart_sendhex(dht11_data[0]);*/
        /*uart_sendhex(dht11_data[2]);*/
    }
}
