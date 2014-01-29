/**
 * initialize fan
 */
void initFan() {

  //sets the frequency for the specified pin
  SetPinFrequencySafe(pwmFanPin, fanPwmFrequency);

}  

/**
 * calculate fan speed from resistance given by potentiometer
 */
void setFanSpeed() {

  int fanSpeed;
  // calculate fan speed depending from the temperature on the copper
  // fan needs values[0,255]
  if (peltierPwmValue < 0) fanSpeed = map(inputData.tempBrown, 20, 40, minFanSpeed, 255);
  if (peltierPwmValue > 0) fanSpeed = map(inputData.tempBrown, 20, 0, minFanSpeed, 255);


  // neither heating nor cooling, run the fan at minimum speed.
  if (peltierPwmValue == 0) fanSpeed = minFanSpeed;

  if (fanSpeed > 255) fanSpeed = 255;
  if (fanSpeed < minFanSpeed) fanSpeed = minFanSpeed;
  inputData.fanSpeed = fanSpeed;

  // use this functions instead of analogWrite on 'initialized' pins
  // set the value of a pwm output pin
  pwmWrite(pwmFanPin, fanSpeed);


}


