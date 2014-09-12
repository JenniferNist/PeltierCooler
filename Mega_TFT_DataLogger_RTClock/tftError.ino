/**
 * print error with opening (or creating) the logging file
 */
void printDataFail() {

  tft.println("Error opening tempData.txt");
  tft.println("");
}

/**
 * printed, if SD chard check failed
 */
void printSDFail() {

  tft.println("Initializing SD card...");
  tft.println("initialization failed!");
  tft.println("");
}

/**
 * blue termometer could't be found
 */
void printErrorTempBlue() {
  tft.println("No blue termometer");
}

/**
 * brown termometer could't be found
 */
void printErrorTempBrown() {
  tft.println("No brown termometer");
}

/**
 * water termometer could't be found
 */
void printErrorTempWater() {
  tft.println("No water termometer");
}

/**
 * User should check the missing sensor and restart.
 */
void printCheckAndRestart() {
  tft.println("");
  tft.setTextColor(ST7735_RED);
  tft.println("Please check the missing");
  tft.println("sensor(s) and restart!");
  tft.setTextColor(ST7735_WHITE);
}


/**
 * Some of the temperature sensors isn't workind correctly!
 * The peltier is not working anymore.
 */
void printRuntimeErrors() {

  tft.setCursor(0,40); 
  if (errorFlag.errorTempSensor) {
    tft.setTextColor(ST7735_RED);
    tft.println("Error with an Sensor.");
    tft.println("Please check them.");
    tft.setTextColor(ST7735_WHITE);
    return;
  }  
  if (errorFlag.errorPeltierMaxTemp) {
    tft.setTextColor(ST7735_RED);
    tft. println("Peltier has reached his");
    tft. println("maximum temperature.");
    tft.setTextColor(ST7735_WHITE);
  }
  if (errorFlag.errorPeltierTempDiff) {
    tft.setTextColor(ST7735_RED);
    tft.println("The difference of the two sides");
    tft.println("of the Peltier is to high");
    tft.setTextColor(ST7735_WHITE);
  }
}

