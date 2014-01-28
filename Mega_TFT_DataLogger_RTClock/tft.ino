
/*
** count and print the number of found devices on tft 
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

/*
** initialize tft, black screen and landscape
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

/*
** write static text on tft
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
  tft.print("The target temperature is: ");
  tft.println(inputData.tempTarget);
  
  // fan speed
  tft.setCursor(0, 40);
  tft.print("Fan speed: ");
  tft.setCursor(90, 32);
  tft.println("%");
  
  // peltier element
  tft.setCursor(0, 72);
  tft.print("Peltier is ");
  tft.println("off");

}

/*
** if the time has changed, print the current time on tft
 */
void tftPrintTime() {
  static time_t tLast;

  t = now();
  if (t != tLast) {
    tLast = t;
    
    dateStringGenerator();

    tft.fillRect(0, 56, 126, 7, ST7735_BLACK);
    tft.setCursor(0,56);
    tft.println(dateString);

  }
} 


/*
** print the currect temperatur values on tft
 ** but befor: print old time in black color, to vanisch the old data
 */
void tftPrintTemp() {

  // sensor blue
  if (inputData.tempBlue != oldInputData.tempBlue) {
    tft.setCursor(45,0);
    tft.setTextColor(ST7735_BLACK);
    tft.print(oldInputData.tempBlue);
    tft.setCursor(45,0);
    tft.setTextColor(ST7735_WHITE);
    tft.print(inputData.tempBlue);
  }

  // sensor brown
  if  (inputData.tempBrown != oldInputData.tempBrown) {
    tft.setCursor(45,8);
    tft.setTextColor(ST7735_BLACK);
    tft.print(oldInputData.tempBrown);
    tft.setCursor(45,8);
    tft.setTextColor(ST7735_WHITE);
    tft.print(inputData.tempBrown);
  }

  // sensor water
  if  (inputData.tempWater != oldInputData.tempWater) {
    tft.setCursor(45,16);
    tft.setTextColor(ST7735_BLACK);
    tft.print(oldInputData.tempWater);
    tft.setCursor(45,16);
    tft.setTextColor(ST7735_WHITE);
    tft.println(inputData.tempWater);
  }
  
  // target temperature
  if (inputData.targetTemperature != oldInputData.targetTemperature) {
    // TODO: check for position! is 45 correct??
    tft.setCursor(45,24);
    tft.setTextColor(ST7735_BLACK);
    tft.print(oldInputData.tempTarget);
    tft.setCursor(45,24);
    tft.setTextColor(ST7735_WHITE);
    tft.println(inputData.tempTarget);
  }
}

/*
** print the currect speed of the fan on tft
** but befor: print old time in black color, to vanisch the old data
** oldInputData set in getTempData()
*/
void tftPrintFanSpeed() {
  if (inputData.fanSpeed != oldInputData.fanSpeed) {
    tft.setCursor(72, 40);
    tft.setTextColor(ST7735_BLACK);
    tft.print(oldInputData.fanSpeed);
    tft.setCursor(72, 40);
    tft.setTextColor(ST7735_WHITE);
    tft.print(inputData.fanSpeed);
  }
}

/*
** print information about the peltier
*/
void tftPrintPeltierInfo() {
  if (peltierInfo.peltierHeating) {
    
    // change output only if the peltier was not heating before!
    if (peltierInfo.peltierHeating != oldPeltierInfo.peltierHeating) {
      tft.setCursor(68, 72);
      tft.fillRect(68, 72, 160, 7, ST7735_BLACK);
      tft.println("heating");
    }
  }
  else if (peltierInfo.peltierCooling) {
    
    // change output only if the peltier was not cooling before!
    if (peltierInfo.peltierCooling != oldPeltierInfo.peltierCooling) {
      tft.setCursor(68, 72);
      tft.fillRect(68, 72, 160, 7, ST7735_BLACK);
      tft.println("cooling");
    }
  }
  else if (!peltierInfo.peltierHeating && !peltierInfo.peltierCooling) {
    
    // change output on tft onlay if the peltier was not off before!
    if ((peltierInfo.peltierCooling != oldPeltierInfo.peltierCooling) &&
        (peltierInfo.peltierHeating != oldPeltierInfo.peltierHeating)) {
          tft.setCursor(68, 72);
          tft.fillRect(68, 72, 160, 7, ST7735_BLACK);
          tft.println("off");
    }
    
  } 
}

/*
** print errors
 */
void checkForErrors() {

  if(errorFlag.errorInitSD) {
    tft.println("Initializing SD card...");
    tft.println("initialization failed!");
    tft.println("");
    
  } 
  else {
    tft.println("Initializing SD card...");
    tft.println("initialization done.");
    tft.println("");
  }
  if (errorFlag.errorTempData) {
    tft.println("Error opening tempData.txt");
    tft.println("");
  }
  if (errorFlag.errorBlue) tft.println("No blue termometer");
  if (errorFlag.errorBrown) tft.println("No brown termometer");
  if (errorFlag.errorWater) tft.println("No water termometer");
  //if (errorFlag.errorBlue || errorFlag.errorBrown || errorFlag.errorWater) while(true);

}

