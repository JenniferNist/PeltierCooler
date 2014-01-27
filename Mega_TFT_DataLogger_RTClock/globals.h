#ifndef _GLOBALS_H
#define _GLOBALS_H


// define struct for needed information
typedef struct inputDataType {
  float tempBlue = 0;
  float tempBrown = 0;
  float tempWater = 0;
  float tempTarget = 24;
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
};

errorFlagType errorFlag;

// varialbes for RTClock
time_t t;

// strings for output on tft and log on sd-card
String dateString = "";
String dataLogString = "";

// arrays to hold Temperature Sensor device addresses
DeviceAddress blueTermometer, brownTermometer, waterTermometer;

// read three sensors and append to the string:
char buffer[40];

// variables for fan
int fan = 3;                // the pin that the LED is attached to
int32_t frequency = 25000;  // frequency of the pwn-signal (in Hz)


// potentiometer
const int poti = A0;        // the analog pin, the poti is attached to

// needed as globals??
int n = 1;                  // initialize counter


#endif // _GLOBALS_H
