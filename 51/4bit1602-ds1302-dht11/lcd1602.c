#include "delay.h"
#include "lcd1602.h"
#include "common.h"

#define LCD_DB P2

sbit LCD_RS = P0 ^ 0;
sbit LCD_EN = P0 ^ 2;
sbit LCD_RW = P0 ^ 1;

void lcdWriteCmd(unsigned char cmd)
{
    //lcd_check_busy();
    Delay600us();
    LCD_EN = 0;
    
    LCD_RS = 0;
    //LCD_RW = 0;
    LCD_DB = (LCD_DB & 0x0F) | (cmd & 0xF0);
    LCD_EN = 1;
    LCD_EN = 0;
    LCD_DB = (LCD_DB & 0x0F) | (cmd << 4);
    LCD_EN = 1;
    LCD_EN = 0;
}

void lcdWriteDat(unsigned char dat)
{
    /*lcd_check_busy();*/
    Delay600us();
    LCD_EN = 0;
    LCD_RS = 1;
    //LCD_RW = 0;
    LCD_DB = (LCD_DB & 0x0F) | (dat & 0xF0);
    LCD_EN = 1;
    LCD_EN = 0;
    LCD_DB = (LCD_DB & 0x0F) | (dat << 4);
    LCD_EN = 1;
    LCD_EN = 0;
}

void lcdSetCursor(unsigned char x, unsigned char y)
{
    unsigned char addr;

    if (x == 0) 
        addr = 0x80 + y;
    else
        addr = 0xC0 + y;
    lcdWriteCmd(addr); 
}

/**/
void lcdShowStr(unsigned char x, unsigned char y, unsigned char *str, unsigned char len)
{
    lcdSetCursor(x, y);

    while (len--)
        lcdWriteDat(*str++);
}	

void write_str(unsigned char addr_start, unsigned char* str)
{
    lcdWriteCmd(addr_start);
    while (*str != '\0')
    {
        lcdWriteDat(*str++);
    }
}

void write_char(unsigned char x, unsigned char y, unsigned char dat)
{
    lcdSetCursor(x, y);
    lcdWriteDat(dat);
}

void initLcd1602()
{
    lcd_light_back = 0; //初始化打开背光
    LCD_RW = 0;
    lcdWriteCmd(0x33); 	
    Delay4ms();
    lcdWriteCmd(0x32); 
    Delay4ms();
    lcdWriteCmd(0x28); 	
    lcdWriteCmd(0x0c);	
    lcdWriteCmd(0x06);	
    lcdWriteCmd(0x01);	
    Delay200ms();
}

//--------------------------------------------------------------------------
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

void flicker_minute(unsigned char x)
{
    display_min(x);
    Delay500ms();
    write_char(1, 3, ' ');
    write_char(1, 4, ' ');
    Delay500ms();
}

void display_hour(unsigned char x)
{
    unsigned char i, j;
    i = x / 10; //取十位
    j = x % 10; //取个位
    write_char(1, 0, i + '0');
    write_char(1, 1, j + '0');
}

void flicker_hour(unsigned char x)
{
    display_hour(x);
    Delay500ms();
    write_char(1, 0, ' ');
    write_char(1, 1, ' ');
    Delay500ms();
}

void display_day(unsigned char x)
{
    unsigned char i, j;
    i = x / 10; //取十位
    j = x % 10; //取个位
    write_char(0, 8, i + '0');
    write_char(0, 9, j + '0');
}

void flicker_day(unsigned char x)
{
    display_day(x);
    Delay500ms();
    write_char(0, 8, ' ');
    write_char(0, 9, ' ');
    Delay500ms();
}

void display_month(unsigned char x)
{
    unsigned char i, j;
    i = x / 10; //取十位
    j = x % 10; //取个位
    write_char(0, 5, i + '0');
    write_char(0, 6, j + '0');
}

void flicker_month(unsigned char x)
{
    display_month(x);
    Delay500ms();
    write_char(0, 5, ' ');
    write_char(0, 6, ' ');
    Delay500ms();
}

void display_year(unsigned char x)
{
    unsigned char i, j;
    i = x / 10; //取十位
    j = x % 10; //取个位
    write_char(0, 2, i + '0');
    write_char(0, 3, j + '0');
}

void flicker_year(unsigned char x)
{
    write_char(0, 0, '2');
    write_char(0, 1, '0');
    display_year(x);
    Delay500ms();
    write_char(0, 0, ' ');
    write_char(0, 1, ' ');
    write_char(0, 2, ' ');
    write_char(0, 3, ' ');
    Delay500ms();
}

void display_week(unsigned char x)
{
    unsigned char i, j;
    i = x / 10; //取十位
    j = x % 10; //取个位
    write_char(0, 11, i + '0');
    write_char(0, 12, j + '0');
}

void flicker_week(unsigned char x)
{
    display_week(x);
    Delay500ms();
    write_char(0, 11, ' ');
    write_char(0, 12, ' ');
    Delay500ms();
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

void display_dht11()
{
    unsigned char i, j;
    //dht11因为2秒钟才读一次，所以只需要2秒钟更新下显示就行
    if (dht11_data[5]) {
        dht11_data[5] = 0; //清除dht11显示标志

        i = dht11_data[0] / 10; //湿度十位
        j = dht11_data[0] % 10; //湿度个位
        write_char(1, 9, i + '0');
        write_char(1, 10, j + '0');
        write_char(1, 11, '%');
        write_char(1, 12, ' ');
    
        i = dht11_data[2] / 10; //温度十位
        j = dht11_data[2] % 10; //温度个位
        write_char(1, 13, i + '0');
        write_char(1, 14, j + '0');
        write_char(1, 15, 'C');
    }
}
