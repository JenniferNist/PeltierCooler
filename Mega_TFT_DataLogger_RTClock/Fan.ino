/*
** initialize fan
*/
void initFan() {
  
  //initialize all timers except for 0, to save time keeping functions
  InitTimersSafe(); 

  //sets the frequency for the specified pin
  SetPinFrequencySafe(fan, frequency);

}  

/*
** calculate fan speed from resistance given by potentiometer
*/
void getFanSpeed() {
    
  int speed = analogRead(poti); // return from analogRead [0,1023]
  
  // mapping [0,1023] to [30,255] because fan needs values[0,255] 
  int speedFan = map(speed, 0, 1023, 30, 255);  
  inputData.fanSpeed = map(speedFan, 0, 256, 0, 100); 
  
  // use this functions instead of analogWrite on 'initialized' pins
  // set the value of a pwm output pin
  pwmWrite(fan, speedFan);

}
