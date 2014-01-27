
#include <Adafruit_GFX.h>          // Core graphics library
#include <Adafruit_ST7735.h>       // Hardware-specific library
#include <SD.h>                    // library to work with SD-Cards
#include <SPI.h>                   // SPI library 
#include <OneWire.h>               
#include <DallasTemperature.h>

#include <DS3232RTC.h>        // http://github.com/JChristensen/DS3232RTC
#include <Time.h>             // http://playground.arduino.cc/Code/Time
#include <Wire.h>             // http://arduino.cc/en/Reference/Wire
#include <PWM.h>              // XYZ
#include <peltierControl.h>   // selfmade library specially for the peltier element


#include "config.h"
#include "globals.h"

// Setup a oneWire instance to communicate with any OneWire devices (not just Maxim/Dallas temperature ICs)
OneWire oneWire(ONE_WIRE_BUS);

// Pass our oneWire reference to Dallas Temperature. 
DallasTemperature sensors(&oneWire);

// TFT - SPI connection
Adafruit_ST7735 tft = Adafruit_ST7735(tft_cs, dc, rst);


void setup()
{
  // Open serial communications and wait for port to open:
  Serial.begin(115200);
  sensors.begin();

  initRTC();
  initTempSensors();
  initFan();
  initTft();
  initSD();

  locateTempSensors();
  checkForErrors();
  delay(4000); 
  
  writeStaticText();

}

void loop()
{
  
  updateTimeFromSerial();
  
  getTempData();
  getFanSpeed();
  
  tftPrintTime();
  tftPrintTemp();
  tftPrintFanSpeed();
  
  logDataOnSD();

}



