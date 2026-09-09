#include <stdint.h>
#ifndef UART_SERIAL_H
#define UART_SERIAL_H

extern void uart_init();
extern void uart_printchar(char c);
extern void uart_printstr(char *data);
extern void uart_println(char *data);
extern void uart_printint(int32_t n);

#endif // UART_SERIAL_H