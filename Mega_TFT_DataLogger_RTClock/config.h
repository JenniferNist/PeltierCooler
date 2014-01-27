#ifndef _CONFIG_H
#define _CONFIG_H

/*
 *  pins connected to Arduino MEGA 2560 as follows:
 **
 ** rst - pin -1          // display reset (Adafruit TS7735)
 ** poti - pin A0         // potentiometer analog pin
 ** 
 ** pwmPeltierPin - pin 5 // peltier element - PWM - timer 3
 ** pwmFanPin - pin 6     // fan - PWM - timer 4
 **
 ** I2C SDA - pin 20      // RTClock
 ** I2C SCL - pin 21      // RTClock
 **
 ** oneWire - pin 40      // temperature sensors (ds18b20)
 ** heatingPin - pin 42   // peltier element
 ** coolingPin - pin 43   // peltier element
 **
 ** dc - pin 48           // display (Adafruit TS7735)
 ** sd_cs - pin 49        // display (Adafruit TS7735)
 ** MISO - pin 50         // display (Adafruit TS7735) - SPI
 ** MOSI - pin 51         // display (Adafruit TS7735) - SPI
 ** CLK - pin 52          // display (Adafruit TS7735) - SPI
 ** tft_cs - pin 53       // display (Adafruit TS7735) - SPI
 */

// 
#define poti A0
#define rst  -1
#define pwmPeltierPin 7 
#define pwmFanPin 6
#define heatingPin 42
#define coolingPin 43
#define dc   48
#define sd_cs 49
#define tft_cs   53

// Data wire is plugged into port 40 on the Arduino
#define ONE_WIRE_BUS 40

// set precision of the temperature sensors to 12 bit
#define TEMPERATURE_PRECISION 12

// set frequency of fan and peltier element
#define fanPwmFrequency 22000  // frequency of the pwn-signal (in Hz)
#define peltierPwmFrequency 22000  // frequency of the pwn-signal (in Hz)

#endif // _CONFIG_H
