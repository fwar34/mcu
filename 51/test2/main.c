#include <reg52.h>
#include "lcd1602.h"
#include "delay.h"

#define CKSEL           (*(unsigned char volatile xdata *)0xfe00)
#define CKDIV           (*(unsigned char volatile xdata *)0xfe01)
#define IRC24MCR        (*(unsigned char volatile xdata *)0xfe02)
#define XOSCCR          (*(unsigned char volatile xdata *)0xfe03)
#define IRC32KCR        (*(unsigned char volatile xdata *)0xfe04)
sfr P_SW2 = 0xba;

sbit led = P0 ^ 5;
sbit lcd_light = P0 ^ 3;

void delay(unsigned int count)
{
    unsigned int i, j;
    for (i = 0; i < count; ++i) {
        for (j = 0; j < 400; ++j);
    }
}

void main()
{
    P_SW2 = 0x80;
    XOSCCR = 0xc0;                              //??????
    while (!(XOSCCR & 1));                      //??????
    CKDIV = 0x00;                               //?????
    CKSEL = 0x01;                               //??????
    P_SW2 = 0x00;
    
    beep = 1;
    //initLcd1602();

    while (1) {
        led = !led;
        lcd_light = !lcd_light;
        delay(1000);
        //write_char(0, 0, 't');
    }
}