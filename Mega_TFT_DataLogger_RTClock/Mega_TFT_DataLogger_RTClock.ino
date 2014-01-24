/*
 * SD card attached to SPI bus as follows:
 ** MOSI - pin 51
 ** MISO - pin 50
 ** CLK - pin 52
 ** SD CS - pin 49 
 */

#include <Adafruit_GFX.h>    // Core graphics library
#include <Adafruit_ST7735.h> // Hardware-specific library
#include <SD.h>
#include <SPI.h>
#include <OneWire.h>
#include <DallasTemperature.h>

#include <DS3232RTC.h>        //http://github.com/JChristensen/DS3232RTC
#include <Time.h>             //http://playground.arduino.cc/Code/Time
#include <Wire.h>             //http://arduino.cc/en/Reference/Wire



// For the breakout, you can use any (2 or) 3 pins
#define tft_cs   53
#define dc   48
#define rst  -1  // you can also connect this to the Arduino reset
#define sd_cs 49

// Data wire is plugged into port 40 on the Arduino
#define ONE_WIRE_BUS 40
#define TEMPERATURE_PRECISION 12

typedef struct inputDataType{
  float tempBlue;
  float tempBrown;
  float tempWater;
  float tempTarget;
};

inputDataType inputData;
inputDataType oldInputData;

/////////////////////////////////////////////////////////


// Setup a oneWire instance to communicate with any OneWire devices (not just Maxim/Dallas temperature ICs)
OneWire oneWire(ONE_WIRE_BUS);

// Pass our oneWire reference to Dallas Temperature. 
DallasTemperature sensors(&oneWire);

// arrays to hold device addresses
DeviceAddress blueTermometer, brownTermometer, waterTermometer;

// in case of an error
boolean errorBlue, errorBrown, errorWater;
boolean errorInitSD;

Adafruit_ST7735 tft = Adafruit_ST7735(tft_cs, dc, rst);

static time_t tLast;
time_t t;
tmElements_t tm;

File myFile;
String dateString = "";
String dataLogString = "";


/////////////////////////////////////////////////////////////

void setup()
{
  // Open serial communications and wait for port to open:
  Serial.begin(115200);
  sensors.begin();

  initRTC();
  initTempSensors();
  initTft();
  initSD();
  delay(2000);
  
  locateTempSensors();
  writeStaticText();

}

void loop()
{
  updateTimeFromSerial();
  getTempData();
  logDataOnSD();
  tftPrintTime();
  tftPrintTemp();


}


