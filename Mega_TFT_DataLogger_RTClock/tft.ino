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
  tft.println(dateString);
  tft.println("");

  // sensor water
  tft.setCursor(10, 8);
  tft.print("Water temp:");
  tft.setCursor(126,8);
  tft.println("C");

  // target temperature
  tft.setCursor(10, 16);
  tft.print("Target temp:");
  tft.setCursor(126,16);
  tft.println("C");

  // system info
  tft.setCursor(0, 32);
  tft.println("System information:");

  tft.setCursor(10, 40);
  tft.print("Peltier down:");
  tft.setCursor(126,40);
  tft.println("C");

  // sensor brown
  tft.setCursor(10,48);
  tft.print("Peltier up:");
  tft.setCursor(126,48);
  tft.println("C");

  // peltier element
  tft.setCursor(10, 56);
  tft.print("Peltier is ");
  // print next word in an different color
  tft.setTextColor(ST7735_GREEN);
  tft.setCursor(90, 56);
  tft.println("off");
  // resetcolor
  tft.setTextColor(ST7735_WHITE);
  // Print Value of peltier
  tft.setCursor(10, 64);
  tft.println("Peltier intensity: ");
  
  // fan speed
  tft.setCursor(10, 72);
  tft.print("Fan speed: ");
  tft.setCursor(110, 72);
  tft.println("%");
  
  // Errors
  tft.setCursor(0,88);
  tft.println("Errors:");
  
  // Current errors
  tft.setCursor(10, 96);
  tft.println("None");
  
  
}

////////////////////////////// Print changing values ////////////////////////////////////
// Time
// Temperature
// Fan speed
// Peltier Infomation


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

    printChangedChar(oldTimeString, currentTimeString, 0, 0);

    tLast = currentTime;
  }
} 


/**
 * print the currect temperatur values on tft
 * but befor: print old time in black color, to vanisch the old data
 */
void tftPrintTemp() {

  if (!reprintTemp) {

    // sensor blue 
    // overwrite only if the value has changed
    if (inputData.tempBlue != oldInputData.tempBlue) {

      String tempBlueOld = floatToString(buffer, oldInputData.tempBlue, 2, 4);
      String tempBlueCurrent = floatToString(buffer, inputData.tempBlue, 2, 4);

      printChangedChar(tempBlueOld, tempBlueCurrent, 90, 48);  
    }

    // sensor brown
    // overwrite only if the value has changed
    if  (inputData.tempBrown != oldInputData.tempBrown) {

      String tempBrownOld = floatToString(buffer, oldInputData.tempBrown, 2, 4);
      String tempBrownCurrent = floatToString(buffer, inputData.tempBrown, 2, 4);

      printChangedChar(tempBrownOld, tempBrownCurrent, 90, 40);   

    }

    // sensor water
    // overwrite only if the value has changed
    if  (inputData.tempWater != oldInputData.tempWater) {

      String tempWaterOld = floatToString(buffer, oldInputData.tempWater, 2, 4);
      String tempWaterCurrent = floatToString(buffer, inputData.tempWater, 2, 4);

      printChangedChar(tempWaterOld, tempWaterCurrent, 90, 8);  

    }

    // target temperature
    // overwrite only if the value has changed
    if  (inputData.tempTarget != oldInputData.tempTarget) {

      String tempTargetOld = floatToString(buffer, oldInputData.tempTarget, 2, 4);
      String tempTargetCurrent = floatToString(buffer, inputData.tempTarget, 2, 4);

      printChangedChar(tempTargetOld, tempTargetCurrent, 90, 16);  
    }
  }
  else {

    String tempBlue = floatToString(buffer, inputData.tempBlue, 2, 4);
    tft.setCursor(45, 0);
    tft.print(tempBlue);  

    String tempBrown = floatToString(buffer, inputData.tempBrown, 2, 4);  
    tft.setCursor(45, 8);
    tft.print(tempBrown);  

    String tempWater = floatToString(buffer, inputData.tempWater, 2, 4);
    tft.setCursor(45, 16);
    tft.print(tempWater);  

    String tempTarget = floatToString(buffer, inputData.tempTarget, 2, 4);
    tft.setCursor(45, 24);
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
      tft.fillRect(90, 72, 20, 8, ST7735_BLACK);
      tft.setCursor(90, 72);
      tft.print(printFanSpeed);
    }
  }
  else {
    tft.setCursor(90, 72);
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
      tft.setCursor(90, 56);
      tft.fillRect(90, 56, 42, 8, ST7735_BLACK);
      // print next word in an different color and size
      tft.setTextColor(ST7735_RED);
      tft.println("heating");
      // reset color
      tft.setTextColor(ST7735_WHITE);  
      break;

    case PeltierCooling:
      tft.setCursor(90, 56);
      tft.fillRect(90, 56, 42, 8, ST7735_BLACK);
      // print next word in an different color and size
      tft.setTextColor(ST7735_CYAN);
      tft.println("cooling");
      // reset color
      tft.setTextColor(ST7735_WHITE);
      break;

    case PeltierStopped:
      tft.setCursor(90, 56);
      tft.fillRect(90, 56, 42, 8, ST7735_BLACK);
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
  

  if (!reprintFanSpeed){
  
  // peltier value
  // overwrite only if the value has changed
  if  (peltierPwmValue != oldPeltierPwmValue) {

    String peltierPwmValueOld = itoa(oldPeltierPwmValue, buffer, 10);
    String peltierPwmValueCurrent = itoa(peltierPwmValue, buffer, 10);

    printChangedChar(peltierPwmValueOld, peltierPwmValueCurrent, 120, 64);  
    oldPeltierPwmValue = peltierPwmValue;
  }
  }else {
    String peltierPwmValueCurrent = itoa(peltierPwmValue, buffer, 10);
    tft.setCursor(120, 64);
    tft.print(peltierPwmValueCurrent);
    reprintFanSpeed = false;
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



