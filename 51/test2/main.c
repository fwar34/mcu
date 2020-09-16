#include <reg52.h>
//#include "lcd1602.h"
#include "ds1302.h"
#include "delay.h"
#include "infrared.h"

sfr P0M0        =   0x94;
sfr P0M1        =   0x93;
sfr P1M0        =   0x92;
sfr P1M1        =   0x91;
sfr P2M0        =   0x96;
sfr P2M1        =   0x95;
sfr P3M0        =   0xb2;
sfr P3M1        =   0xb1;
sfr P4M0        =   0xb4;
sfr P4M1        =   0xb3;
sfr P5M0        =   0xca;
sfr P5M1        =   0xc9;
sfr P6M0        =   0xcc;
sfr P6M1        =   0xcb;
sfr P7M0        =   0xe2;
sfr P7M1        =   0xe1;

#define CKSEL           (*(unsigned char volatile xdata *)0xfe00)
#define CKDIV           (*(unsigned char volatile xdata *)0xfe01)
#define IRC24MCR        (*(unsigned char volatile xdata *)0xfe02)
#define XOSCCR          (*(unsigned char volatile xdata *)0xfe03)
#define IRC32KCR        (*(unsigned char volatile xdata *)0xfe04)
sfr P_SW2 = 0xba;

sbit led = P0 ^ 5;
sbit lcd_light = P0 ^ 3;

sbit P15 = P1 ^ 5;
sbit P16 = P1 ^ 6;
sbit P17 = P1 ^ 7;
sbit P32 = P3 ^ 2;

void delay(unsigned int count)
{
    unsigned int i, j;
    for (i = 0; i < count; ++i) {
        for (j = 0; j < 400; ++j);
    }
}

void main()
{
    DS1302_TIME start_time = {20, 9, 9, 3, 0, 6, 40};
    DS1302_TIME current_time;
//    P_SW2 = 0x80;
//    XOSCCR = 0xc0;                              //??????
//    while (!(XOSCCR & 1));                      //??????
//    CKDIV = 0x00;                               //?????
//    CKSEL = 0x01;                               //??????
//    P_SW2 = 0x00;
    
    P0M1 = 0x00;
        P0M0 = 0x00;

        P1M1 = 0x00;         
        P1M0 = 0x00;

        P2M1 = 0x00;
        P2M0 = 0x00;

        P3M1 = 0x00;
        P3M0 = 0x00;

        P4M1 = 0x00;
        P4M0 = 0x00;

        P5M1 = 0x00;
        P5M0 = 0x00;

        P6M1 = 0x00;
        P6M0 = 0x00;

        P7M1 = 0x00;
        P7M0 = 0x00;
    
    
    ds1302_init();
    IrInit();

    
    beep = 1;
    //initLcd1602();

    while (1) {
        ds1302_read_time(&current_time);

        led = !led;
        lcd_light = !lcd_light;
        P15 = !P15;
        P16 = !P16;
        P17 = !P17;
        P32 = !P32;
        delay(1000000);
        //write_char(0, 0, 't');
    }
}