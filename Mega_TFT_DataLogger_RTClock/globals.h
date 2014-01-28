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
// boolean errorFan = false;  --> not jet implemented --> how?
// boolean errorPeltier = false --> not jet implemented --> how?
};

errorFlagType errorFlag;

// define struct for peltier information
typedef struct peltierInfoType {
  boolean peltierHeating = false;
  boolean peltierCooling = false;
  // int peltierPercentage = 0;
};

peltierInfoType peltierInfo;
peltierInfoType oldPeltierInfo;


// varialbes for RTClock
time_t t;

// strings for output on tft and log on sd-card
String dateString = "";
String dataLogString = "";

// arrays to hold Temperature Sensor device addresses
DeviceAddress blueTermometer, brownTermometer, waterTermometer;

// range for the changable target temperature
// target Temperature (tempTarget) by potentiometer
float minTemperature = 15;
float maxTemperature = 30;

// set adressos of the devices (temperature sensors)
// --> does not compile jet!!
// blueTermometer = 288CA5C50200009F;
// brownTermometer = 288785C50200009F;
// waterTermometer = not jet known;

// read three sensors and append to the string:
char buffer[40];


#endif // _GLOBALS_H
