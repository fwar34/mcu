#include <intrins.h>
#include "delay.h"

void Delay600us()		//@12.000MHz
{
    unsigned char i, j;

    _nop_();
    _nop_();
    i = 7;
    j = 253;
    do
    {
        while (--j);
    } while (--i);
}

void Delay4ms()		//@12.000MHz
{
    unsigned char i, j;

    _nop_();
    _nop_();
    i = 47;
    j = 173;
    do
    {
        while (--j);
    } while (--i);
}

void Delay200ms()		//@12.000MHz
{
    unsigned char i, j, k;

    i = 10;
    j = 31;
    k = 147;
    do
    {
        do
        {
            while (--k);
        } while (--j);
    } while (--i);
}

void Delay50ms()		//@12.000MHz
{
    unsigned char i, j, k;

    i = 3;
    j = 72;
    k = 161;
    do
    {
        do
        {
            while (--k);
        } while (--j);
    } while (--i);
}

void Delay1ms()		//@11.0592MHz
{
	unsigned char i, j;

	_nop_();
	i = 11;
	j = 190;
	do
	{
		while (--j);
	} while (--i);
}

void Delay2us()		//@11.0592MHz
{
	unsigned char i;

	_nop_();
	_nop_();
	i = 2;
	while (--i);
}

void Delay10us()		//@12.000MHz
{
    unsigned char i;

    i = 27;
    while (--i);
}

void Delay20ms()		//@12.000MHz
{
    unsigned char i, j, k;

    i = 1;
    j = 234;
    k = 113;
    do
    {
        do
        {
            while (--k);
        } while (--j);
    } while (--i);
}

void Delay30us()		//@12.000MHz
{
    unsigned char i;

    i = 87;
    while (--i);
}

void Delay50us()		//@12.000MHz
{
    unsigned char i, j;

    _nop_();
    _nop_();
    i = 1;
    j = 145;
    do
    {
        while (--j);
    } while (--i);
}

void Delay1000ms()		//@12.000MHz
{
    unsigned char i, j, k;

    i = 46;
    j = 153;
    k = 245;
    do
    {
        do
        {
            while (--k);
        } while (--j);
    } while (--i);
}

void Delay2000ms()		//@12.000MHz
{
    unsigned char i, j, k;

    i = 92;
    j = 50;
    k = 238;
    do
    {
        do
        {
            while (--k);
        } while (--j);
    } while (--i);
}

void Delay600ms()		//@12.000MHz
{
    unsigned char i, j, k;

    i = 28;
    j = 92;
    k = 196;
    do
    {
        do
        {
            while (--k);
        } while (--j);
    } while (--i);
}

void Delay5us()//@12.000MHz
{
    unsigned char i;

    i = 12;
    while (--i);
    
}

void Delay1us()		//@11.0592MHz
{
	_nop_();
}

void Delay2ms()		//@11.0592MHz
{
	unsigned char i, j;

	i = 22;
	j = 128;
	do
	{
		while (--j);
	} while (--i);
}

void delay_us1(unsigned char count)
{
    unsigned char i;
    for (i = 0; i < count; ++i) {
        _nop_();
    }
}

void delay_us2(unsigned char count)
{
    unsigned char i;
    for (i = 0; i < count / 2; ++i) {
        unsigned char i;

	_nop_();
	_nop_();
	i = 2;
	while (--i);
    }
}

void delay_ms1(unsigned char count)
{
    unsigned char i;
    for (i = 0; i < count; ++i) {
        unsigned char i, j;

        _nop_();
        i = 11;
        j = 190;
        do
        {
            while (--j);
        } while (--i);
    }
}

void delay_ms2(unsigned char count)
{
    unsigned char i;
    for (i = 0; i < count / 2; ++i) {
        unsigned char i, j;

	i = 22;
	j = 128;
	do
	{
		while (--j);
	} while (--i);
    }
}
