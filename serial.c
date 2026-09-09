// Ako F_CPU nije definiran, build env nije setupan kako treba
// setbaud.h ce svejedno bacit error

// Postavljanje baudrate-a za uart
#include "serial.h"

#include <avr/io.h>
#include <avr/sfr_defs.h>
#include <stdlib.h>

#define BAUD 115200
#include <util/setbaud.h>





void uart_init() {
    UBRR0H = UBRRH_VALUE;
    UBRR0L = UBRRL_VALUE;
    UCSR0C = (_BV(UCSZ01) | _BV(UCSZ00));
    UCSR0B = _BV(TXEN0);
    
    // Neke brzine zahtjevaju ovo, header setbaud.h ce postaviti makro
    // pri compile time-u
    // Vidi poglavlje 19.11 u datasheetu
    #if USE_2X
    UCSR0A |= (1 << U2X0);
    #else
    UCSR0A &= ~(1 << U2X0);
    #endif
}

void uart_printchar(char c) {
    loop_until_bit_is_set(UCSR0A, UDRE0);
    UDR0 = c;
}

void uart_printstr(char *data) {
    while(*data)
        uart_printchar(*data++);
}

void uart_println(char *data) {
    while(*data)
        uart_printchar(*data++);
    // Carriadge Return \r i Line Feed \n za pravilne new lineove, aka CRLF
    uart_printchar('\r');
    uart_printchar('\n');
}

void uart_printint(int32_t n)  {
    char str[11]; // Max int_32 ima 10 znamenki, +1 za \0
    itoa(n, str, 10);
    uart_println(str);
}
