/**
 * print errors
 */
void checkForInitErrors() {

  if(errorFlag.errorInitSD) {
    printSDFail();
  } 
  else {
    printSDOk();
  }

  if (errorFlag.errorTempData) {
    printDataFail();
  }

  if (errorFlag.errorBlue || errorFlag.errorBrown || errorFlag.errorWater) {
    PC.stop();
    pwmWrite(pwmFanPin, 0);

    if (errorFlag.errorBlue) printErrorTempBlue();
    if (errorFlag.errorBrown) printErrorTempBrown();
    if (errorFlag.errorWater) printErrorTempWater();
    printCheckAndRestart();

    while(true);
    //{
      //getTempData();

      // Check, if the down-side of the peltier is to hot
      //if (inputData.tempBlue > 26) {
      //}
      //else {
        //PC.stop();
      //}
    //}
  }
}

/**
 * check for serious errors
 */
void checkForErrors() {

  setErrorFlags();

  if (errorFlag.errorPeltierMaxTemp || errorFlag.errorTempSensor || errorFlag.errorPeltierTempDiff) {
    PC.stop();
    pwmWrite(pwmFanPin, 255);
    ClearTft();
    printRuntimeErrors();

    
    while(errorFlag.errorTempSensor)
    {
      getTempData();
      setErrorFlags();
      PC.stop();
    }
    ClearTft();
    reprintTemp = true;
    reprintFanSpeed = true;
    reprintValue = true;
    reprintPeltierInfo = true;
    writeStaticText();
  }
}



/**
 * Set flags if an serious error occured.
 */
void setErrorFlags() {

  // TODO: Lesefehler von den Sensoren sind nicht unüblich, damit muss gerechnet werden, obwohl sie funktionieren!
  // Besser: letzte temperatur und letzte "gute" Zeit speichern, alte temperatur solange an das system weiterreichen, bis
  // längere Zeit keine "gute" Temperatur mehr gelesen wird.

  int tempDifference = abs (inputData.tempBlue - inputData.tempBrown);

  // should any sensor stop working or is not plugged in stop immediatly
  if (inputData.tempBlue <= -85.00 || inputData.tempBrown <= -85.00 || inputData.tempWater <= -85.00) {
    errorFlag.errorTempSensor = true;
  }
  else {
    errorFlag.errorTempSensor = false;
  }
  return;

  // peltier element can not stand to have a temperature difference of over 60C
  if (tempDifference > maxTempDifference) {
    errorFlag.errorPeltierTempDiff = true;
  }

  // the peltier shall not get too hot
  if (inputData.tempBrown > maxHeatingTemp) {
    errorFlag.errorPeltierMaxTemp = true;
  }
}






