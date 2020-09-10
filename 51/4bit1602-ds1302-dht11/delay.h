#ifndef _DELAY_H_
#define _DELAY_H_

void Delay1us();		//@11.0592MHz
void Delay2ms();		//@11.0592MHz
void Delay600us();		//@12.000MHz
void Delay4ms();		//@12.000MHz
void Delay200ms();		//@12.000MHz
void Delay50ms();		//@12.000MHz
void Delay1ms();		//@12.000MHz
void Delay2us();		//@12.000MHz
void Delay10us();		//@12.000MHz
void Delay20ms();		//@12.000MHz
void Delay30us();		//@12.000MHz
void Delay50us();		//@12.000MHz
void Delay1000ms();		//@12.000MHz
void Delay2000ms();		//@12.000MHz
void Delay600ms();		//@12.000MHz
void Delay5us();                //@12.000MHz

void delay_us1(unsigned char count);
void delay_us2(unsigned char count);
void delay_ms1(unsigned char count);
void delay_ms2(unsigned char count);
    
#endif
