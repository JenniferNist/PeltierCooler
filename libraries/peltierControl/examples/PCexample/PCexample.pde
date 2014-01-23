#include <peltierControl.h>

int pwmPin = 9;		                                // Define intensity/pwm pin as 9
int heatingPin = 2;		                        // Define heating pin as 2
int coolingPin = 3;		                        // Define cooling pin as 3

PC PC(pwmPin, heatingPin, coolingPin);

void setup()
{
 PC.begin();	                                        // Initialize PC library and define pins 
 PC.stop();				                // Set initial intensity and direction to 0
}

void loop(){
  PC.heat(255);						// Test run conrol heat at max intensity
  delay(1000);						// Wait one second
  PC.heat(0);						// Stop running
  delay(100);						// switch of the peltier
  PC.cool(255);						// run control in cooling at max intensity
  delay(1000);						// Wait one second
  PC.cool(0);						// Stop running
  delay(100);						// switch of the peltier
}
