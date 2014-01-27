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

// varialbes for RTClock
time_t t;

// strings for output on tft and log on sd-card
String dateString = "";
String dataLogString = "";

// arrays to hold Temperature Sensor device addresses
DeviceAddress blueTermometer, brownTermometer, waterTermometer;

// read three sensors and append to the string:
char buffer[40];

// the pin that the fan is attached to
int fan = 3;

// the analog pin, the potentiometer is attached to
const int poti = A0;

// pins for peltier
int pwmPin = 5;		                                // Define intensity/pwm pin as 5
int heatingPin = 6;		                        // Define heating pin as 6
int coolingPin = 7;		                        // Define cooling pin as 7


#endif // _GLOBALS_H
