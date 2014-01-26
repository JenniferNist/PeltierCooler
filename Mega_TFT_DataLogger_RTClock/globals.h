#ifndef _GLOBALS_H
#define _GLOBALS_H


// define struct for needed information
typedef struct inputDataType{
  float tempBlue;
  float tempBrown;
  float tempWater;
  float tempTarget;
};

inputDataType inputData;
inputDataType oldInputData;

// varialbes for RTClock
time_t t;


// strings for output on tft and log on sd-card
String dateString = "";
String dataLogString = "";

// arrays to hold Temperature Sensor device addresses
DeviceAddress blueTermometer, brownTermometer, waterTermometer;

// in case of an error
boolean errorBlue, errorBrown, errorWater;
boolean errorInitSD;

// read three sensors and append to the string:
char buffer[40];


#endif // _GLOBALS_H
