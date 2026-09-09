#include "pumpa.h"
#include <avr/io.h>

void pumpa_init(void)
{
    DDRD |= (1 << PD3);
    PORTD &= ~(1 << PD3);
}

void pumpa_on(void)
{
    PORTD |= (1 << PD3);}

void pumpa_off(void)
{
    PORTD &= ~(1 << PD3);
}