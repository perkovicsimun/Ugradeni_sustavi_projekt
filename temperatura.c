#include "temperatura.h"

#include <avr/io.h>
#include <util/delay.h>
#include <stdint.h>

#include "pindef.h"
#include "onewire.h"
#include "ds18b20.h"

static const gpin_t temp_pin = {
    &PORTD,
    &PIND,
    &DDRD,
    PD6
};

void temperatura_init(void)
{
}

float temperatura_read(void)
{
    if(!onewire_reset(&temp_pin))
    {
        return -1000.0;
    }

    ds18b20_convert(&temp_pin);
    _delay_ms(750);

    uint16_t raw = ds18b20_read_single(&temp_pin);

    if(raw == kDS18B20_CrcCheckFailed ||
       raw == kDS18B20_DeviceNotFound)
    {
        return -1000.0;
    }

    return ((float)raw) / 16.0;
}