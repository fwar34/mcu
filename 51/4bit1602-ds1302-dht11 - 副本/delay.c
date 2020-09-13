#include <intrins.h>
#include "delay.h"

void Delay100us()		//@24.000MHz
{
	unsigned char i, j;

	i = 4;
	j = 27;
	do
	{
		while (--j);
	} while (--i);
}

void Delay20ms()		//@24.000MHz
{
	unsigned char i, j, k;

	_nop_();
	i = 3;
	j = 112;
	k = 91;
	do
	{
		do
		{
			while (--k);
		} while (--j);
	} while (--i);
}

void Delay30us()		//@24.000MHz
{
	unsigned char i;

	i = 238;
	while (--i);
}

void Delay5us()		//@24.000MHz
{
	unsigned char i;

	i = 38;
	while (--i);
}

void Delay7ms()		//@24.000MHz
{
	unsigned char i, j;

	_nop_();
	_nop_();
	i = 219;
	j = 43;
	do
	{
		while (--j);
	} while (--i);
}

void Delay10us()		//@24.000MHz
{
	unsigned char i;

	i = 78;
	while (--i);
}

void Delay50ms()		//@24.000MHz
{
	unsigned char i, j, k;

	_nop_();
	i = 7;
	j = 23;
	k = 105;
	do
	{
		do
		{
			while (--k);
		} while (--j);
	} while (--i);
}

void Delay600us()		//@24.000MHz
{
	unsigned char i, j;

	i = 19;
	j = 177;
	do
	{
		while (--j);
	} while (--i);
}

void Delay4ms()		//@24.000MHz
{
	unsigned char i, j;

	_nop_();
	i = 125;
	j = 170;
	do
	{
		while (--j);
	} while (--i);
}
    
void Delay200ms()		//@24.000MHz
{
	unsigned char i, j, k;

	_nop_();
	_nop_();
	i = 25;
	j = 90;
	k = 176;
	do
	{
		do
		{
			while (--k);
		} while (--j);
	} while (--i);
}

void Delay500ms()		//@24.000MHz
{
	unsigned char i, j, k;

	_nop_();
	_nop_();
	i = 61;
	j = 225;
	k = 62;
	do
	{
		do
		{
			while (--k);
		} while (--j);
	} while (--i);
}

void Delay1us()		//@24.000MHz
{
	unsigned char i;

	i = 6;
	while (--i);
}

void Delay2ms()		//@24.000MHz
{
	unsigned char i, j;

	_nop_();
	_nop_();
	i = 63;
	j = 83;
	do
	{
		while (--j);
	} while (--i);
}

void Delay1ms()		//@24.000MHz
{
	unsigned char i, j;

	_nop_();
	i = 32;
	j = 40;
	do
	{
		while (--j);
	} while (--i);
}
