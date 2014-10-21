//////////////////////////////// Initializing ///////////////////////////

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
 * printed, if SD chard check was ok
 */
void printSDOk() {

  tft.println("Initializing SD card...");
  tft.println("initialization done.");
  tft.println("");
  tft.println("");
}

/////////////////////////////////// Static Text //////////////////////////////////////

/**
 * write static text on tft
 */
void writeStaticText() {

  tft.fillScreen(ST7735_BLACK);
  tft.setCursor(0,0);

  // date
  dateStringGenerator(currentTime);
  tft.setTextColor(ST7735_GREEN);
  tft.println(dateString);
  tft.setTextColor(ST7735_WHITE);
  tft.println("");

  // sensor water
  tft.setCursor(10, 10);
  tft.print("Water temp:");
  tft.setCursor(90,10);
  tft.println("00.00 C");

  // target temperature
  tft.setCursor(10, 20);
  tft.print("Target temp:");
  tft.setCursor(90,20);
  tft.println("00.00 C");

  // system info
  tft.setCursor(0, 40);
  tft.setTextColor(ST7735_GREEN);
  tft.println("Peltier information:");
  tft.setTextColor(ST7735_WHITE);

  tft.setCursor(10, 50);
  tft.print("Temp bottom:");
  tft.setCursor(90,50);
  tft.println("00.00 C");

  // sensor brown
  tft.setCursor(10,60);
  tft.print("Temp top:");
  tft.setCursor(90,60);
  tft.println("00.00 C");

  // peltier element
  tft.setCursor(10, 70);
  tft.print("Peltier is ");
  // print next word in an different color
  tft.setTextColor(ST7735_GREEN);
  tft.setCursor(90, 70);
  tft.println("off");
  // resetcolor
  tft.setTextColor(ST7735_WHITE);
  // Print Value of peltier
  tft.setCursor(10, 80);
  tft.println("Intensity: ");
  tft.setCursor(90, 80);
  tft.println("0");
  tft.setCursor(110, 80);
  tft.println("%");

  // fan speed
  tft.setCursor(10, 90);
  tft.print("Fan speed: ");
  tft.setCursor(90, 90);
  tft.print("0");
  tft.setCursor(110, 90);
  tft.println("%");
}

////////////////////////////// Print changing values ////////////////////////////////////
// Time
// Temperature
// Fan speed
// Peltier Infomation

// flag to check, if a second passed
boolean nextSecond = false;

/**
 *if the time has changed, print the current time on tft
 */
void tftPrintTime() {

  static time_t tLast;
  String oldTimeString = "";
  String currentTimeString = "";

  if (currentTime != tLast) {

    oldTimeString = dateStringGenerator(tLast);
    currentTimeString = dateStringGenerator(currentTime);

    tft.setTextColor(ST7735_GREEN);
    printChangedChar(oldTimeString, currentTimeString, 0, 0);
    tft.setTextColor(ST7735_WHITE);

    tLast = currentTime;
    nextSecond = true;
    
  } else {
    nextSecond = false;
  }
} 


/**
 * print the currect temperatur values on tft
 * but befor: print old time in black color, to vanisch the old data
 */
void tftPrintTemp() {

  if (!reprintTemp) {

    if (nextSecond) {
    // sensor blue 
    // overwrite only if the value has changed
    if (inputData.tempBlue != oldInputData.tempBlue) {

      String tempBlueOld = floatToString(buffer, oldInputData.tempBlue, 2, 4);
      String tempBlueCurrent = floatToString(buffer, inputData.tempBlue, 2, 4);

      printChangedChar(tempBlueOld, tempBlueCurrent, 90, 50);  
    }

    // sensor brown
    // overwrite only if the value has changed
    if  (inputData.tempBrown != oldInputData.tempBrown) {

      String tempBrownOld = floatToString(buffer, oldInputData.tempBrown, 2, 4);
      String tempBrownCurrent = floatToString(buffer, inputData.tempBrown, 2, 4);

      printChangedChar(tempBrownOld, tempBrownCurrent, 90, 60);   

    }

    // sensor water
    // overwrite only if the value has changed
    if  (inputData.tempWater != oldInputData.tempWater) {

      String tempWaterOld = floatToString(buffer, oldInputData.tempWater, 2, 4);
      String tempWaterCurrent = floatToString(buffer, inputData.tempWater, 2, 4);

      printChangedChar(tempWaterOld, tempWaterCurrent, 90, 10);  

    }

    // target temperature
    // overwrite only if the value has changed
    if  (inputData.tempTarget != oldInputData.tempTarget) {

      String tempTargetOld = floatToString(buffer, oldInputData.tempTarget, 2, 4);
      String tempTargetCurrent = floatToString(buffer, inputData.tempTarget, 2, 4);

      printChangedChar(tempTargetOld, tempTargetCurrent, 90, 20);  
    }
    nextSecond = false;
    }
  }
  else {

    String tempBlue = floatToString(buffer, inputData.tempBlue, 2, 4);
    tft.setCursor(90, 50);
    tft.fillRect(90, 50, 30, 8, ST7735_BLACK);
    tft.print(tempBlue);  

    String tempBrown = floatToString(buffer, inputData.tempBrown, 2, 4);  
    tft.setCursor(90, 60);
    tft.fillRect(90, 60, 30, 8, ST7735_BLACK);
    tft.print(tempBrown);  

    String tempWater = floatToString(buffer, inputData.tempWater, 2, 4);
    tft.setCursor(90, 10);
    tft.fillRect(90, 10, 30, 8, ST7735_BLACK);
    tft.print(tempWater);  

    String tempTarget = floatToString(buffer, inputData.tempTarget, 2, 4);
    tft.setCursor(90, 20);
    tft.fillRect(90, 20, 30, 8, ST7735_BLACK);
    tft.print(tempTarget);  

    reprintTemp = false;
  }
}

/**
 * print the currect speed of the fan on tft
 * but befor: print old time in black color, to vanisch the old data
 * oldInputData set in getTempData()
 */
void tftPrintFanSpeed() {

  if (!reprintFanSpeed) {

    if (inputData.fanSpeed != oldInputData.fanSpeed) {
      int printFanSpeed = map(inputData.fanSpeed, 0, 255, 0, 100);
      tft.fillRect(90, 90, 20, 8, ST7735_BLACK);
      tft.setCursor(90, 90);
      tft.print(printFanSpeed);
    }
  }
  else {
    tft.setCursor(90, 90);
    int printFanSpeed = map(inputData.fanSpeed, 0, 255, 0, 100);
    tft.print(printFanSpeed);
    reprintFanSpeed = false;
  }
}

// variable for previous peltier state
PeltierState oldPeltierState = PC.peltierState;
int oldPeltierPwmValue = 999;

/**
 * print information about the peltier
 */
void tftPrintPeltierInfo() {

  if ((oldPeltierState != PC.peltierState) || reprintPeltierInfo) {
    switch(PC.peltierState) {

    case PeltierHeating:
      tft.setCursor(90, 70);
      tft.fillRect(90, 70, 42, 8, ST7735_BLACK);
      // print next word in an different color and size
      tft.setTextColor(ST7735_RED);
      tft.println("heating");
      // reset color
      tft.setTextColor(ST7735_WHITE);  
      break;

    case PeltierCooling:
      tft.setCursor(90, 70);
      tft.fillRect(90, 70, 42, 8, ST7735_BLACK);
      // print next word in an different color and size
      tft.setTextColor(ST7735_CYAN);
      tft.println("cooling");
      // reset color
      tft.setTextColor(ST7735_WHITE);
      break;

    case PeltierStopped:
      tft.setCursor(90, 70);
      tft.fillRect(90, 70, 42, 8, ST7735_BLACK);
      // print next word in an different color and size
      tft.setTextColor(ST7735_GREEN);
      tft.println("off");
      // resetcolor
      tft.setTextColor(ST7735_WHITE);
      break;
    }
    oldPeltierState = PC.peltierState;
    reprintPeltierInfo = false;
  }

  if (!reprintValue){

    // peltier value
    // overwrite only if the value has changed
    if  (peltierPwmValue != oldPeltierPwmValue) {

      int printPwmValueMapped = map(abs(peltierPwmValue), 0, 255, 0, 100);
      tft.fillRect(90, 80, 20, 8, ST7735_BLACK);
      tft.setCursor(90, 80);
      tft.print(printPwmValueMapped);
      oldPeltierPwmValue = peltierPwmValue;
    } 
  }
   else { 
      tft.setCursor(90, 80);
      int printPwmValueMapped = map(abs(peltierPwmValue), 0, 255, 0, 100);
      tft.print(printPwmValueMapped);
      reprintValue = false;   
  }
}

//////////////////////////////////////////////////////////////////////////////////////

/**
 * Clear tft.
 */
void ClearTft() {
  tft.fillScreen(ST7735_BLACK);
  tft.setCursor(0,0);
}

/**
 * Print only the changed charaters on tft.
 */
void printChangedChar(String oldString, String currentString, int posX, int posY) {

  int length;
  int length1 = oldString.length();
  int length2 = currentString.length();

  if (length1 > length2) {
    length = length1;
  }
  else {
    length = length2;
  } 

  for(int i = 0; i < (length + 1); i++) {

    char old = oldString[i];
    char current = currentString[i];

    // draw only the different chars on tft
    if(old != current) {

      int charPosX = posX + (i * 6); // 5 pixels per char plus one empty line
      tft.fillRect(charPosX, posY, 6, 8, ST7735_BLACK);
      tft.setCursor(charPosX, posY);
      tft.print(current);    
    }
  } 
}





