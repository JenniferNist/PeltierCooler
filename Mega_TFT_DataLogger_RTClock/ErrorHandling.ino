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
  if (errorFlag.errorBlue) printErrorTempBlue();
  if (errorFlag.errorBrown) printErrorTempBrown();
  if (errorFlag.errorWater) printErrorTempWater();
}

/**
 * check for temperature difference of the two sides of the peltier element
 */
void checkForErrors() {

  int tempDifference = abs (inputData.tempBlue - inputData.tempBrown);

  // peltier element can not stand to have a temperature difference of over 60C
  if (tempDifference > maxTempDifference) {
    // TODO: tempDifference wird ab hier nicht mehr aktualisiert!
    // Besser: hier nur flags setzen!
    PC.stop();
    pwmWrite(pwmFanPin, 255);
    while(true);
  }


  // TODO: Lesefehler von den Sensoren sind nicht unüblich, damit muss gerechnet werden, obwohl sie funktionieren!
  // Besser: letzte temperatur und letzte "gute" Zeit speichern, alte temperatur solange an das system weiterreichen, bis
  // längere Zeit keine "gute" Temperatur mehr gelesen wird.

  // hier: nur flag setzen.

  // should any sensor stop working or is not plugged in stop immediatly
  //while(inputData.tempBlue <= -85.00 || inputData.tempBrown <= -85.00 || inputData.tempBrown <= -85.00) {
  //PC.stop();


  // the peltier shall not get too hot
  if (inputData.tempBrown > maxHeatingTemp) {
    PC.stop();
    pwmWrite(pwmFanPin, 255);
    while(true);
  }

  if (errorFlag.errorBlue) printErrorTempBlue();
  if (errorFlag.errorBrown) printErrorTempBrown();
  if (errorFlag.errorWater) printErrorTempWater();

}




