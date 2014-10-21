#ifndef _GLOBALS_H
#define _GLOBALS_H

// Setup a OneWire instance to communicate with any OneWire devices.
// OneWire oneWire(ONE_WIRE_BUS);

// Pass our oneWire reference to Dallas Temperature.
// DallasTemperature sensore(&oneWire);

// encoder to set the target temperature
// Encoder myEnc(encoderA, encoderB);

// TFT - SPI connection
// Adafruit_ST7735 tft = Adafruit_ST7735(tft_cs, dc, rst);

// peltier control: heat or cool
// PC PC(pwmPeltierPin, heatingPin, coolingPin, peltierPwmFrequency);

// define struct for needed information
typedef struct inputDataType {
  float tempBlue = 0;
  float tempBrown = 0;
  float tempWater = 0;
  float tempTarget = 0;
  int fanSpeed = 0;           // fan speed in percentage
};

inputDataType inputData;
inputDataType oldInputData;

//define struct of error flags
typedef struct errorFlagType {
  boolean errorInitSD = false;
  boolean errorTempData = false;
  boolean errorBlue = false;
  boolean errorBrown = false;
  boolean errorWater = false;
  boolean errorTempSensor = false;
  boolean errorPeltierMaxTemp = false;
  boolean errorPeltierTempDiff = false;
  // boolean errorFan = false;  --> not jet implemented --> how?
  // boolean errorPeltier = false --> not jet implemented --> how?
};

errorFlagType errorFlag;

// variable for peltier element
int peltierPwmValue = 0; // [-255;255]


// Inner boundary for the temperature controller in centi-degrees
int hysteresis = 2;
// Outer boundary for the temperature controller in centi-degrees
int epsilon = 3;


// varialbes for RTClock
time_t currentTime;

// strings for output on tft and log on sd-card
String dateString = "";
String dataLogString = "";

// range for the changable target temperature
// target Temperature (tempTarget) by potentiometer
float minTemperature = 15;
float maxTemperature = 30;

// read three sensors and append to the string:
char buffer[40];

// boolean value for reprint
boolean reprintTemp = false;
boolean reprintFanSpeed = false;
boolean reprintValue = false;
boolean reprintPeltierInfo = false;

#endif // _GLOBALS_H


