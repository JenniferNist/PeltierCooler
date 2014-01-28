/*
** initialize fan
*/
void initFan() {
  
  //sets the frequency for the specified pin
  SetPinFrequencySafe(pwmFanPin, fanPwmFrequency);

}  

/*
** calculate fan speed from resistance given by potentiometer
*/
void getFanSpeed() {
  
  // calculate fan speed depending from the temperature on the copper
  // copper is the heat conductor of the peltier

  // fan needs values[0,255]
  int speedFan = map(inputData.tempBrown, 24, 60, 0, 255);
  speedFan = map(inputData.tempBrown, -20, 22, 0, 255);
  
  if ((inputData.tempBrown <-20) || (inputData.tempBrown > 60)) speedFan = 255;

  // use this functions instead of analogWrite on 'initialized' pins
  // set the value of a pwm output pin
  pwmWrite(pwmFanPin, speedFan);

}
