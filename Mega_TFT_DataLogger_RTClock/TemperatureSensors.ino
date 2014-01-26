/*
** initialize temperature sensors
 */
void initTempSensors() {

  // set the resolution
  sensors.setResolution(blueTermometer, TEMPERATURE_PRECISION);
  sensors.setResolution(brownTermometer, TEMPERATURE_PRECISION);
  sensors.setResolution(waterTermometer, TEMPERATURE_PRECISION);

  //inputData.tempBlue = 0;
  //inputData.tempBrown = 0;
  //inputData.tempWater = 0;
  //inputData.tempTarget = 24;

}

/*
** print found (temperatur) devices
 ** set flag, wether a termometer is found or not
 */
void locateTempSensors() {

  tftFoundDevices();

  errorBlue = false;
  errorBrown = false;
  errorWater = false;

  // debug output if no sensors could be found
  if (!sensors.getAddress(blueTermometer, 0)) {
    errorBlue = true;
  }
  if (!sensors.getAddress(brownTermometer, 2)) {
    errorBrown = true;
  } 
  if (!sensors.getAddress(waterTermometer, 1)) {
    errorWater = true;
  }   

  errorTempSensors(errorBlue, errorBrown, errorWater); 
}

/*
** save old temperature values
 ** get new temperatur values
 */
void getTempData() {

  oldInputData = inputData;

  // call sensors.requestTemperatures() to issue a global temperature 
  // request to all devices on the bus
  sensors.requestTemperatures();
  inputData.tempBlue = sensors.getTempC(blueTermometer);
  inputData.tempBrown = sensors.getTempC(brownTermometer);
  inputData.tempWater = sensors.getTempC(waterTermometer);

}


