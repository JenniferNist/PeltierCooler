#include <poldriv.h>

int pwmPin = 9;		                                //Define speed/pwm pin as 9
int fwdPin = 2;		                                //Define forward pin as 2
int revPin = 3;		                                //Define reverse pin as 3

PD PD(pwmPin, fwdPin, revPin);

void setup()
{
 PD.begin();	                                        //Initialize PD library and define pins 
 PD.stop();				                //Set initial speed and direction to 0
}

void loop(){
  PD.forward(255);					//Test run driver forward at max speed
  delay(1000);						//Wait one second
  PD.forward(0);					//Stop running
  delay(100);						//Wait for motor to slow down
  PD.reverse(255);					//run driver in reverse at max speed
  delay(1000);						//Wait one second
  PD.reverse(0);					//Stop running
  delay(100);						//Wait for motor to slow down
}