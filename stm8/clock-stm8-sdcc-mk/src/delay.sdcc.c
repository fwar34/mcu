#include "stm8s.h"
#include "delay.sdcc.h"

void Delay600us()//@11.0592MHz
{
    unsigned char i, j;

    nop();
    nop();
    i = 9;
    j = 155;
    do
    {
        while (--j);
    } while (--i);
}

void Delay4ms()//@11.0592MHz
{
    unsigned char i, j;

    nop();
    nop();
    i = 58;
    j = 112;
    do
    {
        while (--j);
    } while (--i);
}


void Delay200ms()//@11.0592MHz
{
    unsigned char i, j, k;

    i = 12;
    j = 57;
    k = 122;
    do
    {
        do
        {
            while (--k);
        } while (--j);
    } while (--i);
}


void Delay50ms()//@11.0592MHz
{
    unsigned char i, j, k;

    i = 3;
    j = 207;
    k = 28;
    do
    {
        do
        {
            while (--k);
        } while (--j);
    } while (--i);
}


void Delay1ms()//@11.0592MHz
{
    unsigned char i, j;

    i = 15;
    j = 90;
    do
    {
        while (--j);
    } while (--i);
}

void Delay2us()//@11.0592MHz
{
    unsigned char i;

    nop();
    i = 5;
    while (--i);
}

void Delay10us()//@11.0592MHz
{
    unsigned char i;

    i = 35;
    while (--i);
}

void Delay20ms()//@11.0592MHz
{
    unsigned char i, j, k;

    i = 2;
    j = 32;
    k = 60;
    do
    {
        do
        {
            while (--k);
        } while (--j);
    } while (--i);
}

void Delay30us()//@11.0592MHz
{
    unsigned char i;

    nop();
    nop();
    i = 108;
    while (--i);
}

void Delay50us()//@11.0592MHz
{
    unsigned char i;

    nop();
    i = 182;
    while (--i);
}

void Delay1000ms()//@11.0592MHz
{
    unsigned char i, j, k;

    i = 57;
    j = 27;
    k = 112;
    do
    {
        do
        {
            while (--k);
        } while (--j);
    } while (--i);
}

void Delay2000ms()//@11.0592MHz
{
    unsigned char i, j, k;

    i = 113;
    j = 53;
    k = 228;
    do
    {
        do
        {
            while (--k);
        } while (--j);
    } while (--i);
}

void Delay600ms()//@11.0592MHz
{
    unsigned char i, j, k;

    nop();
    i = 34;
    j = 170;
    k = 117;
    do
    {
        do
        {
            while (--k);
        } while (--j);
    } while (--i);
}

void Delay5us()//@11.0592MHz
{
    unsigned char i;

    nop();
    i = 16;
    while (--i);
}

void Delay1us()//@11.0592MHz
{
    unsigned char i;

    nop();
    nop();
    i = 1;
    while (--i);
}

void Delay2ms()//@11.0592MHz
{
    unsigned char i, j;

    i = 29;
    j = 183;
    do
    {
        while (--j);
    } while (--i);
}

void Delay7ms()//@11.0592MHz
{
    unsigned char i, j;

    i = 101;
    j = 135;
    do
    {
        while (--j);
    } while (--i);
}

void Delay100us()//@11.0592MHz
{
    unsigned char i, j;

    i = 2;
    j = 109;
    do
    {
        while (--j);
    } while (--i);
}

void Delay500ms()//@11.0592MHz
{
    unsigned char i, j, k;

    i = 29;
    j = 14;
    k = 54;
    do
    {
        do
        {
            while (--k);
        } while (--j);
    } while (--i);
}
