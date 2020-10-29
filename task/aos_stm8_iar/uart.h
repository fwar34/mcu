#ifndef _UART_H_
#define _UART_H_

void uart_init();
void uart_send_byte(unsigned char Data);
void uart_send_string(char* str);

#endif
