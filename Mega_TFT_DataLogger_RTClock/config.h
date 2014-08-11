#ifndef _CONFIG_H
#define _CONFIG_H

/**
 *  pins connected to Arduino MEGA 2560 as follows:
 *
 * rst - pin -1            // display reset (Adafruit TS7735)
 * 
 * encoderA - pin 2        // encoder channel a - INTERRUPT
 * encoderB - pin 3        // encoder channel b - INTERRUPT
 *
 * pwmFanPin - pin 6       // fan - PWM - timer 4
 * heatingPin - pin 7      // peltier element
 * pwmPeltierPin - pin 8   // peltier element - PWM - timer 4
 * coolingPin - pin 9      // peltier element
 *
 * encoderTamper - pin 18  // encoder tamper - INTERRUPT
 *
 * I2C SDA - pin 20        // RTClock
 * I2C SCL - pin 21        // RTClock
 *
 * oneWire - pin 40        // temperature sensors (ds18b20)
 *
 * dc - pin 48             // display (Adafruit TS7735)
 * sd_cs - pin 49          // display (Adafruit TS7735)
 * MISO - pin 50           // display (Adafruit TS7735) - SPI
 * MOSI - pin 51           // display (Adafruit TS7735) - SPI
 * CLK - pin 52            // display (Adafruit TS7735) - SPI
 * tft_cs - pin 53         // display (Adafruit TS7735) - SPI
 */

#define rst  -1
#define encoderA 2
#define encoderB 3
#define pwmFanPin 6
#define pwmPeltierPin 8
#define heatingPin 7
#define coolingPin 9
#define encoderTamper 18

#define dc   48
#define sd_cs 49
#define tft_cs   53

// Data wire is plugged into port 40 on the Arduino
#define ONE_WIRE_BUS 40

// set precision of the temperature sensors to 12 bit
#define TEMPERATURE_PRECISION 12

#define DS18B20DELAY 1000


// arrays to hold Temperature Sensor device addresses
uint8_t blueTermometer[] = { 0x28, 0xB4, 0x9D, 0xC5, 0x02, 0x00, 0x00, 0x69 };
uint8_t waterTermometer[]   = { 0x28, 0xEC, 0xA9, 0xC5, 0x02, 0x00, 0x00, 0x7D };
uint8_t brownTermometer[] = { 0x28, 0x41, 0xA7, 0xC5, 0x02, 0x00, 0x00, 0xC9 };


// set frequency of fan and peltier element
#define fanPwmFrequency 22000  // frequency of the pwn-signal (in Hz)
#define peltierPwmFrequency 22000  // frequency of the pwn-signal (in Hz)

// maximum difference between the two sides of peltier
#define maxTempDifference 60
// maximum peltier heating side
#define maxHeatingTemp 80

#define minFanSpeed 30

#endif // _CONFIG_H
