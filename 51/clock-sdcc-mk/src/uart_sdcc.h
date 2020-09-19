#ifndef _UART_SDCC_H_
#define _UART_SDCC_H_

#include <stdint.h>

void UART_init();
void UART_send_string(uint8_t *buf);
void UART_send_byte(uint8_t dat);

#endif
