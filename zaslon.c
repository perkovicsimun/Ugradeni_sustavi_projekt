#include "zaslon.h"

#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h>

#define ZASLON_ADDR 0x27

#define ZASLON_BACKLIGHT 0x08
#define ZASLON_ENABLE    0x04
#define ZASLON_RW        0x02
#define ZASLON_RS        0x01

static void i2c_init(void)
{
    TWSR = 0;
    TWBR = 72;
}

static void i2c_start(void)
{
    TWCR = (1 << TWINT) | (1 << TWSTA) | (1 << TWEN);

    while(!(TWCR & (1 << TWINT)));

    TWDR = (ZASLON_ADDR << 1);

    TWCR = (1 << TWINT) | (1 << TWEN);

    while(!(TWCR & (1 << TWINT)));
}

static void i2c_write(uint8_t data)
{
    TWDR = data;

    TWCR = (1 << TWINT) | (1 << TWEN);

    while(!(TWCR & (1 << TWINT)));
}

static void i2c_stop(void)
{
    TWCR = (1 << TWINT) | (1 << TWEN) | (1 << TWSTO);
}

static void zaslon_write4(uint8_t data)
{
    i2c_start();

    i2c_write(data | ZASLON_BACKLIGHT | ZASLON_ENABLE);

    _delay_us(1);

    i2c_write((data | ZASLON_BACKLIGHT) & ~ZASLON_ENABLE);

    i2c_stop();

    _delay_us(50);
}

static void zaslon_send(uint8_t value, uint8_t mode)
{
    uint8_t high = value & 0xF0;
    uint8_t low = (value << 4) & 0xF0;

    zaslon_write4(high | mode);
    zaslon_write4(low | mode);
}

static void zaslon_command(uint8_t command)
{
    zaslon_send(command, 0);
}

static void zaslon_data(uint8_t data)
{
    zaslon_send(data, ZASLON_RS);
}

void zaslon_init(void)
{
    i2c_init();

    _delay_ms(50);

    zaslon_write4(0x30);
    _delay_ms(5);

    zaslon_write4(0x30);
    _delay_us(150);

    zaslon_write4(0x30);
    zaslon_write4(0x20);

    zaslon_command(0x28);
    zaslon_command(0x0C);
    zaslon_command(0x06);

    zaslon_clear();
}

void zaslon_clear(void)
{
    zaslon_command(0x01);
    _delay_ms(2);
}

void zaslon_set_cursor(uint8_t row, uint8_t col)
{
    uint8_t address;

    if(row == 0)
    {
        address = 0x00 + col;
    }
    else
    {
        address = 0x40 + col;
    }

    zaslon_command(0x80 | address);
}

void zaslon_print(char *str)
{
    while(*str)
    {
        zaslon_data(*str++);
    }
}

void zaslon_printint(int32_t n)
{
    char buffer[12];

    ltoa(n, buffer, 10);

    zaslon_print(buffer);
}