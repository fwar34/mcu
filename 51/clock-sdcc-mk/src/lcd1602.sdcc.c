#include "delay.sdcc.h"
#include "lcd1602.sdcc.h"
#include "common.sdcc.h"
#include "uart_sdcc.h"

#define LCD_DB P2

#define LCD_RS P0_0
#define LCD_EN P0_2
#define LCD_RW P0_1

extern unsigned char dht11_data[5];//湿度十位，湿度个位，温度十位，温度个位，是否更新显示的标志


void lcd_check_busy()
{
    __bit lcd_status;

    LCD_RS = 0;
    LCD_RW = 1;

    do
    {
        LCD_EN = 1;
        lcd_status = P2_7;
        LCD_EN = 0;
    } while (lcd_status);
}

void lcdWriteCmd(unsigned char cmd)
{
    /* lcd_check_busy(); */
    Delay600us();
    LCD_EN = 0;
    
    LCD_RS = 0;
    /* LCD_RW = 0; */
    LCD_DB = (LCD_DB & 0x0F) | (cmd & 0xF0);
    LCD_EN = 1;
    LCD_EN = 0;
    LCD_DB = (LCD_DB & 0x0F) | (cmd << 4);
    LCD_EN = 1;
    LCD_EN = 0;
}

void lcdWriteDat(unsigned char dat)
{
    /* lcd_check_busy(); */
    Delay600us();
    LCD_EN = 0;
    LCD_RS = 1;
    /* LCD_RW = 0; */
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
    lcd_light_back = 0;//初始化打开背光
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

void wait_for_dht11()
{
    unsigned char i;
    for (i = 0; i < 16; ++i) {
        write_char(0, i, '>');
        Delay50ms();
    }

    for (i = 15; i == 0; --i) {
        write_char(1, i, '<');
        Delay50ms();
    }
}

//--------------------------------------------------------------------------
void display_sec(unsigned char x)
{
    unsigned char i, j;
    i = x / 10;//取十位
    j = x % 10;//取个位
    write_char(1, 6, i + '0');
    write_char(1, 7, j + '0');
}

void display_min(unsigned char x)
{
    unsigned char i, j;
    i = x / 10;//取十位
    j = x % 10;//取个位
    write_char(1, 3, i + '0');
    write_char(1, 4, j + '0');
}

void flicker_minute(unsigned char x)
{
    write_char(1, 3, ' ');
    write_char(1, 4, ' ');
    Delay500ms();
    display_min(((x & 0x70) >> 4) * 10 + (x & 0x0F));
    Delay500ms();
}

void display_hour(unsigned char x)
{
    unsigned char i, j;
    i = x / 10;//取十位
    j = x % 10;//取个位
    write_char(1, 0, i + '0');
    write_char(1, 1, j + '0');
}

void flicker_hour(unsigned char x)
{
    write_char(1, 0, ' ');
    write_char(1, 1, ' ');
    Delay500ms();
    display_hour(((x & 0x30) >> 4) * 10 + (x & 0x0F));
    Delay500ms();
}

void display_day(unsigned char x)
{
    unsigned char i, j;
    i = x / 10;//取十位
    j = x % 10;//取个位
    write_char(0, 8, i + '0');
    write_char(0, 9, j + '0');
}

void flicker_day(unsigned char x)
{
    write_char(0, 8, ' ');
    write_char(0, 9, ' ');
    Delay500ms();
    display_day(((x & 0x30) >> 4) * 10 + (x & 0x0F));
    Delay500ms();
}

void display_month(unsigned char x)
{
    unsigned char i, j;
    i = x / 10;//取十位
    j = x % 10;//取个位
    write_char(0, 5, i + '0');
    write_char(0, 6, j + '0');
}

void flicker_month(unsigned char x)
{
    write_char(0, 5, ' ');
    write_char(0, 6, ' ');
    Delay500ms();
    display_month(((x & 0x10) >> 4) * 10 + (x & 0x0F));
    Delay500ms();
}

void display_year(unsigned char x)
{
    unsigned char i, j;
    i = x / 10;//取十位
    j = x % 10;//取个位
    write_char(0, 2, i + '0');
    write_char(0, 3, j + '0');
}

void flicker_year(unsigned char x)
{
    write_char(0, 0, ' ');
    write_char(0, 1, ' ');
    write_char(0, 2, ' ');
    write_char(0, 3, ' ');
    Delay500ms();
    write_char(0, 0, '2');
    write_char(0, 1, '0');
    display_year((x >> 4) * 10 + (x & 0x0F));
    Delay500ms();
}

void display_week(unsigned char x)
{
    unsigned char i, j;
    i = x / 10;//取十位
    j = x % 10;//取个位
    write_char(0, 11, i + '0');
    write_char(0, 12, j + '0');
}

void flicker_week(unsigned char x)
{
    write_char(0, 11, ' ');
    write_char(0, 12, ' ');
    Delay500ms();
    display_week(x & 0x07);
    Delay500ms();
}

//秒，分，时，日，月，星期，年
void display()
{
    UART_send_string("display");
    write_char(0, 0, '2');
    write_char(0, 1, '0');
    write_char(0, 4, '-');
    write_char(0, 7, '-');
    write_char(0, 10, '|');
    write_char(1, 2, ':');
    write_char(1, 5, ':');

    display_sec(((current_time.second & 0x70) >> 4) * 10 + (current_time.second & 0x0F));
    display_min(((current_time.minute & 0x70) >> 4) * 10 + (current_time.minute & 0x0F));
    display_hour(((current_time.hour & 0x30) >> 4) * 10 + (current_time.hour & 0x0F));
    display_day(((current_time.day & 0x30) >> 4) * 10 + (current_time.day & 0x0F));
    display_month(((current_time.month & 0x10) >> 4) * 10 +(current_time.month & 0x0F));
    display_week(current_time.week & 0x07);
    display_year((current_time.year >> 4) * 10 + (current_time.year & 0x0F));
}

void display_dht11()
{
    UART_send_string("display_dht11");
    unsigned char i, j;
    /* UART_send_byte(dht11_data[4]); */
    //dht11因为2秒钟才读一次，所以只需要2秒钟更新下显示就行
    if (dht11_data[4]) {
        dht11_data[4] = 0;//清除dht11显示标志

        i = dht11_data[0] / 10;//湿度十位
        j = dht11_data[0] % 10;//湿度个位
        write_char(1, 9, i + '0');
        write_char(1, 10, j + '0');
        write_char(1, 11, '%');
        write_char(1, 12, ' ');
    
        i = dht11_data[2] / 10;//温度十位
        j = dht11_data[2] % 10;//温度个位
        write_char(1, 13, i + '0');
        write_char(1, 14, j + '0');
        write_char(1, 15, 'C');
        /* UART_send_string("dht11_display"); */
    }
}
