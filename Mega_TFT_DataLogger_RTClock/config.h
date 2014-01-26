#ifndef _CONFIG_H
#define _CONFIG_H


/*
 * SD card attached to SPI bus as follows:
 ** MOSI - pin 51
 ** MISO - pin 50
 ** CLK - pin 52
 */

// For the breakout, you can use any (2 or) 3 pins
#define tft_cs   53
#define sd_cs 49
#define dc   48
#define rst  -1  // connected to the Arduino reset

// Data wire is plugged into port 40 on the Arduino
#define ONE_WIRE_BUS 40

// set precision of the temperature sensors to 12 bit
#define TEMPERATURE_PRECISION 12


#endif // _CONFIG_H
