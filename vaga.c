#include "vaga.h"
#include <avr/io.h>
#include <util/delay.h>
#define VAGA_FACTOR 273.25
static int32_t vaga_offset = 0;
void vaga_tare(void)
{
    int64_t suma = 0;

    for(uint8_t i = 0; i < 20; ++i)
    {
        suma += vaga_read();
        _delay_ms(50);
    }

    vaga_offset = suma / 20;
}
void vaga_init(void)
{
    DDRD &= ~(1 << PD4);
    DDRD |= (1 << PD5);
    PORTD &= ~(1 << PD5);
}


float vaga_read_grams(void)
{
    int32_t raw = vaga_read();

    return (raw - vaga_offset) / VAGA_FACTOR;
}
int32_t vaga_read(void)
{
    int32_t value = 0;
    while(PIND & (1 << PD4));

    for(uint8_t i = 0; i < 24; ++i)
    {

        PORTD |= (1 << PD5);
        _delay_us(1);
        value <<= 1;
        if(PIND & (1 << PD4))
        {
            value |= 1;
        }
        PORTD &= ~(1 << PD5);
        _delay_us(1);
    }

    PORTD |= (1 << PD5);
    _delay_us(1);

    PORTD &= ~(1 << PD5);
    _delay_us(1);

    if(value & 0x800000)
    {
        value |= 0xFF000000;
    }

    return value;
}