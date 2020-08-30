#include <reg52.h>
#include "delay.h"
#include "lcd1602.h"

#define LCD_DB P0

sbit LCD_RS = P0 ^ 0;
sbit LCD_EN = P0 ^ 1;

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
