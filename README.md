# Ugradeni_sustavi_projekt
I built a small Arduino-based project for my college course.


Semi-Automatic Bird Watering System
A small embedded systems project developed for a college course using an Arduino Nano (ATmega328P). The system monitors the amount of water in a bird water bowl using a load cell and an HX711 module. When the water level drops below 20%, the system activates a water pump through a transistor and relay. The pump is turned off when the water level reaches 80%. The system also measures ambient temperature using a DS18B20 sensor and displays the current temperature and water level on a 16x2 LCD.

Hardware:
- Arduino Nano (ATmega328P)
- Load cell
- HX711
- DS18B20 temperature sensor
- LCD1602 with PCF8574 I2C module
- 2N2222A transistor
- Omron G5LA-1 12V relay
- Pond pump
- 12V DC power supply

Software:

The firmware is written in C using AVR-GCC. The project is divided into separate modules for the pump, scale, temperature sensor, LCD and UART communication.


NOTE:
DS18B20 Library
DS18B20 and 1-Wire communication is based on the library by Stecman:

https://gist.github.com/stecman/9ec74de5e8a5c3c6341c791d9c233adc
