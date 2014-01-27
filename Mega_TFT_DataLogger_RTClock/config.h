#ifndef _CONFIG_H
#define _CONFIG_H

/*
 *  pins connected to Arduino MEGA 2560 as follows:
 **
 ** rst - pin -1          // display (Adafruit TS7735)
 ** poti - pin A0         // potentiometer
 ** 
 ** fan - pin 3           // fan?? - PWM (needed?)
 ** pwmPin - pin 5        // peltier element - PWM ? or fan?
 ** heatingPin - pin 6    // peltier element - PWM (needed?)
 ** coolingPin - pin 7    // peltier element - PWM (needed?)
 **
 ** oneWire - pin 40      // temperature sensors (ds18b20)
 ** dc - pin 48           // display (Adafruit TS7735)
 ** sd_cs - pin 49        // display (Adafruit TS7735)
 ** MISO - pin 50         // display (Adafruit TS7735) - SPI
 ** MOSI - pin 51         // display (Adafruit TS7735) - SPI
 ** CLK - pin 52          // display (Adafruit TS7735) - SPI
 ** tft_cs - pin 53       // display (Adafruit TS7735) - SPI
 **
 ** I2C SDA - sda         // RTClock
 ** I2C SCL - scl         // RTClock
 */

// For the breakout
#define tft_cs   53
#define sd_cs 49
#define dc   48
#define rst  -1  // connected to the Arduino reset

// Data wire is plugged into port 40 on the Arduino
#define ONE_WIRE_BUS 40

// set precision of the temperature sensors to 12 bit
#define TEMPERATURE_PRECISION 12


#endif // _CONFIG_H
