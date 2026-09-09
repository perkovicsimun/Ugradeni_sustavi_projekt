FILES ?= $(wildcard *.c)
OBJS = $(patsubst %c, %o, $(FILES))

DEVICE     ?= atmega328p
CLOCK      ?= 16000000
PROGRAMMER ?= arduino
PORT       ?= COM3
BAUD       ?= 115200
FILENAME   ?= main

CC          = avr-gcc
OBJCOPY     = avr-objcopy
SIZE        = avr-size
CFLAGS      = -Wall -Os -DF_CPU=$(CLOCK) -mmcu=$(DEVICE)
AVRDUDE     = avrdude

.PHONY: all clean build upload

all: build upload clean

build: $(OBJS)
	$(CC) $(CFLAGS) $^ -o $(FILENAME).elf
	$(OBJCOPY) -j .text -j .data -O ihex $(FILENAME).elf $(FILENAME).hex
	$(SIZE) --format=avr --mcu=$(DEVICE) $(FILENAME).elf

%.o: %.c
	$(info Building object $@)
	$(CC) $(CFLAGS) $< -c -o $@

upload:
	$(AVRDUDE) -v -p $(DEVICE) -c $(PROGRAMMER) -P $(PORT) -b $(BAUD) -U flash:w:$(FILENAME).hex

clean:
	del /q *.o
	del /q *.elf
	del /q *.hex