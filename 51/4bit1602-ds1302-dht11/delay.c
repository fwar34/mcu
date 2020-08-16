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

void Delay1ms()		//@12.000MHz
{
	unsigned char i, j;

	_nop_();
	_nop_();
	i = 12;
	j = 168;
	do
	{
		while (--j);
	} while (--i);
}

void Delay2us()		//@12.000MHz
{
	unsigned char i;

	i = 3;
	while (--i);
}

void Delay10us()		//@12.000MHz
{
	unsigned char i;

	i = 27;
	while (--i);
}

