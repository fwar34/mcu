#ifndef _UART_SDCC_H_
#define _UART_SDCC_H_

void uart_init();//9600bps@16MHz
void uart_send_string(unsigned char *buf);
void uart_send_byte(unsigned char dat);
void uart_send_hex(unsigned char dat);

#endif
