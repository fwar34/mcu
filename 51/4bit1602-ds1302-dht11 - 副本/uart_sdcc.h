#ifndef _UART_SDCC_H_
#define _UART_SDCC_H_

typedef unsigned char uint8_t;
typedef unsigned int uint16_t;

void UART_init();
void UartInit(); //9600bps@11.0592MHz
void UART_send_string(uint8_t *buf);
void UART_send_byte(uint8_t dat);

#endif
