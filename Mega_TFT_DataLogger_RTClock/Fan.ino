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
    
  int speed = analogRead(poti); // return from analogRead [0,1023]
  
  // mapping [0,1023] to [30,255] because fan needs values[0,255] 
  // speedFan is the value fot the fan: not under 30, but up to the top (255)
  int speedFan = map(speed, 0, 1023, 30, 255);  
  // for the output on the tft is a range from 0 to 100 (in percentage) needed
  inputData.fanSpeed = map(speedFan, 0, 256, 0, 100); 
  
  // use this functions instead of analogWrite on 'initialized' pins
  // set the value of a pwm output pin
  pwmWrite(pwmFanPin, speedFan);

}
