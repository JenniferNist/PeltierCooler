
/**
 * count and print the number of found devices on tft 
 */
void tftFoundDevices() {

  tft.setCursor(0,0);
  tft.fillScreen(ST7735_BLACK);
  // locate devices on the 1-wire bus
  tft.println("Locating devices");
  tft.print("Found ");
  tft.print(sensors.getDeviceCount(), DEC);
  tft.println(" devices.");
  tft.println("");

}

/**
 * initialize tft, black screen and landscape
 */
void initTft() {

  // set tft_cs as putput
  pinMode(tft_cs, OUTPUT);

  // If your TFT's plastic wrap has a Black Tab, use the following:
  tft.initR(INITR_BLACKTAB);
  tft.fillScreen(ST7735_BLACK);
  // landscape
  tft.setRotation(3);
  // display is black
  tft.invertDisplay(false);

}

/**
 * write static text on tft
 */
void writeStaticText() {

  tft.fillScreen(ST7735_BLACK);
  tft.setCursor(0,0);

  tft.print("Blue  :");
  tft.setCursor(90,0);
  tft.println("C");

  // sensor brown
  tft.print("Brown :");
  tft.setCursor(90,8);
  tft.println("C");

  // sensor water
  tft.print("Water :");
  tft.setCursor(90,16);
  tft.println("C");

  // target temperature
  tft.setCursor(0, 24);
  tft.print("Target:");
  tft.setCursor(90,24);
  tft.println("C");

  // fan speed
  tft.setCursor(0, 40);
  tft.print("Fan speed: ");
  tft.setCursor(90, 40);
  tft.println("%");

  // peltier element
  tft.setCursor(0, 80);
  tft.print("Peltier is ");

  // print next word in an different color
  tft.setTextColor(ST7735_GREEN);
  tft.println(" off");
  // resetcolor
  tft.setTextColor(ST7735_WHITE);

}

/**
 *if the time has changed, print the current time on tft
 */
void tftPrintTime() {

  static time_t tLast;

  if (currentTime != tLast) {
    tLast = currentTime;

    dateStringGenerator();

    tft.fillRect(0, 56, 126, 8, ST7735_BLACK);
    tft.setCursor(0,56);
    tft.println(dateString);

  }
} 


/**
 * print the currect temperatur values on tft
 * but befor: print old time in black color, to vanisch the old data
 */
void tftPrintTemp() {

  // sensor blue 
  // overwrite only if the value has changed
  if (inputData.tempBlue != oldInputData.tempBlue) {
    tft.setCursor(45,0);
    tft.setTextColor(ST7735_BLACK);
    tft.print(oldInputData.tempBlue);
    tft.setCursor(45,0);
    tft.setTextColor(ST7735_WHITE);
    tft.print(inputData.tempBlue);
  }

  // sensor brown
  // overwrite only if the value has changed
  if  (inputData.tempBrown != oldInputData.tempBrown) {
    tft.setCursor(45,8);
    tft.setTextColor(ST7735_BLACK);
    tft.print(oldInputData.tempBrown);
    tft.setCursor(45,8);
    tft.setTextColor(ST7735_WHITE);
    tft.print(inputData.tempBrown);
  }

  // sensor water
  // overwrite only if the value has changed
  if  (inputData.tempWater != oldInputData.tempWater) {
    tft.setCursor(45,16);
    tft.setTextColor(ST7735_BLACK);
    tft.print(oldInputData.tempWater);
    tft.setCursor(45,16);
    tft.setTextColor(ST7735_WHITE);
    tft.println(inputData.tempWater);
  }

  // target temperature
  // overwrite only if the value has changed
  if (inputData.tempTarget != oldInputData.tempTarget) {
    // TODO: check for position! is 45 correct??
    tft.setCursor(45,24);
    tft.setTextColor(ST7735_BLACK);
    tft.print(oldInputData.tempTarget);
    tft.setCursor(45,24);
    tft.setTextColor(ST7735_WHITE);
    tft.println(inputData.tempTarget);
  }
}

/**
 * print the currect speed of the fan on tft
 * but befor: print old time in black color, to vanisch the old data
 * oldInputData set in getTempData()
 */
void tftPrintFanSpeed() {

  if (inputData.fanSpeed != oldInputData.fanSpeed) {
    int printFanSpeed = map(inputData.fanSpeed, 0, 255, 0, 100);
    tft.fillRect(65, 40, 20, 8, ST7735_BLACK);
    tft.setCursor(65, 40);
    tft.print(printFanSpeed);
  }
}

/**
 * print information about the peltier
 */
void tftPrintPeltierInfo() {

  if (peltierPwmValue > 0) {

    tft.setCursor(68, 80);
    tft.fillRect(68, 80, 42, 8, ST7735_BLACK);

    // print next word in an different color and size
    tft.setTextColor(ST7735_RED);
    tft.println("heating");
    // reset color
    tft.setTextColor(ST7735_WHITE);
  }
  else if (peltierPwmValue < 0) {

    tft.setCursor(68, 80);
    tft.fillRect(68, 80, 42, 8, ST7735_BLACK);

    // print next word in an different color and size
    tft.setTextColor(ST7735_CYAN);
    tft.println("cooling");
    // reset color
    tft.setTextColor(ST7735_WHITE);
  }
  else if (peltierPwmValue == 0) {

    tft.setCursor(68, 80);
    tft.fillRect(68, 80, 42, 8, ST7735_BLACK);

    // print next word in an different color and size
    tft.setTextColor(ST7735_GREEN);
    tft.println("off");
    // resetcolor
    tft.setTextColor(ST7735_WHITE);
  }

  tft.fillRect(0, 88, 30, 8, ST7735_BLACK);
  tft.println(peltierPwmValue);
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
 * printed, if SD chard check was ok
 */
void printSDOk() {

  tft.println("Initializing SD card...");
  tft.println("initialization done.");
  tft.println("");
}

/**
 * print error with opening (or creating) the logging file
 */
void printDataFail() {

  tft.println("Error opening tempData.txt");
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


