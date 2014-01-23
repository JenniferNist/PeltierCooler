/*

 Mimics the fade example but with an extra parameter for frequency. It should dim but with a flicker 
 because the frequency has been set low enough for the human eye to detect. This flicker is easiest to see when 
 the LED is moving with respect to the eye and when it is between about 20% - 60% brighness. The library 
 allows for a frequency range from 1Hz - 2MHz on 16 bit timers and 31Hz - 2 MHz on 8 bit timers. When 
 SetPinFrequency()/SetPinFrequencySafe() is called, a bool is returned which can be tested to verify the 
 frequency was actually changed.
 
 This example runs on mega and uno.
 */

#include <OneWire.h>
#include <DallasTemperature.h>
#include <PWM.h>
#include <Wire.h>
#include <LCD.h>
#include <LiquidCrystal_I2C.h>
#include <peltierControl.h>

// Data wire is plugged into port 2 on the Arduino
#define ONE_WIRE_BUS 2
#define TEMPERATURE_PRECISION 11

// Setup a oneWire instance to communicate with any OneWire devices (not just Maxim/Dallas temperature ICs)
OneWire oneWire(ONE_WIRE_BUS);

// Pass our oneWire reference to Dallas Temperature. 
DallasTemperature sensors(&oneWire);

// arrays to hold device addresses
DeviceAddress blueTermometer, brownTermometer, waterTermometer;

// initialize LCD display
LiquidCrystal_I2C  lcd(0x27);

int fan = 3;                // the pin that the LED is attached to
const int poti = A0;        // the analog pin, the poti is attached to
int n = 1;                  // initialize counter
int32_t frequency = 25000;  // frequency of the pwn-signal (in Hz)
int fanSpeed = 0;

// pins for peltier
int pwmPin = 5;		                                // Define intensity/pwm pin as 5
int heatingPin = 6;		                        // Define heating pin as 6
int coolingPin = 7;		                        // Define cooling pin as 7

PC PC(pwmPin, heatingPin, coolingPin);

void setup()
{
  lcd.begin (20,4);
  //initialize all timers except for 0, to save time keeping functions
  InitTimersSafe(); 

  //sets the frequency for the specified pin
  SetPinFrequencySafe(fan, frequency);
  
  // in case of an error
  boolean errorState = false;
  
  // peltier
  PC.begin();	                                        // Initialize PC library and define pins 
  PC.stop();				                // Set initial intensity and direction to 0

  sensors.begin();

  // locate devices on the bus
  lcd.print("Locating devices");
  lcd.setCursor(0,1);
  lcd.print("Found ");
  lcd.print(sensors.getDeviceCount(), DEC);
  lcd.print(" devices.");
  delay(2000);
  lcd.clear();

  // debug output if no sensors could be found
  if (!sensors.getAddress(blueTermometer, 0)) {
    lcd.print("No blue termometer");
    errorState = true; 
  }
  if (!sensors.getAddress(brownTermometer, 2)) {
    lcd.setCursor(0,1);
    lcd.print("No brown termometer");
    errorState = true;
  } 
  if (!sensors.getAddress(waterTermometer, 1)) {
    lcd.setCursor(0,2);
    lcd.print("No water termometer");
    errorState = true;
  }   
  
  // in case of an error blog the program from starting
  if (errorState) {
    while (true);
  }
  
  // set the resolution to 11 bit
  sensors.setResolution(blueTermometer, TEMPERATURE_PRECISION);
  sensors.setResolution(brownTermometer, TEMPERATURE_PRECISION);
  sensors.setResolution(waterTermometer, TEMPERATURE_PRECISION);

  // Switch on the backlight
  lcd.setBacklight(HIGH);
  lcd.home ();                   // go home to position (0,0)
  lcd.print("Fan speed: ");
  lcd.setCursor(15,0);
  lcd.print("%");
}

void loop()
{
  int speed = analogRead(poti); // return from analogRead [0,1023]

  // call sensors.requestTemperatures() to issue a global temperature 
  // request to all devices on the bus
  sensors.requestTemperatures();
  float tempBlue = sensors.getTempC(blueTermometer);
  float tempBrown = sensors.getTempC(brownTermometer);
  float tempWater = sensors.getTempC(waterTermometer);

  // mapping [0,1023] to [30,255] because fan needs values[0,255] 
  int speedFan = map(speed, 0, 1023, 30, 255);  
  fanSpeed = map(speedFan, 0, 256, 0, 100); 

  lcd.setCursor(12,0);  
  lcd.print("   ");
  lcd.setCursor(12,0);
  lcd.print(fanSpeed);

  // sensor blue
  lcd.setCursor(0,1);
  lcd.print("Blue  :");
  lcd.print("        ");
  lcd.setCursor(8,1);
  lcd.print(tempBlue);
  lcd.print(" C");

  // sensor brown
  lcd.setCursor(0,2);
  lcd.print("Brown :");
  lcd.print("      ");
  lcd.setCursor(8,2);
  lcd.print(tempBrown);
  lcd.print(" C");

  // sensor water
  lcd.setCursor(0,3);
  lcd.print("Water :");
  lcd.print("      ");
  lcd.setCursor(8,3);
  lcd.print(tempWater);
  lcd.print(" C");

  //use this functions instead of analogWrite on 'initialized' pins
  pwmWrite(fan, speedFan);

  PC.cool(250);						// Test run conrol heat at max intensity
 
  delay(100);      
}


