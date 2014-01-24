

void tftFoundDevices() {
   
  tft.setCursor(0,0);
  tft.fillScreen(ST7735_BLACK);
  // locate devices on the 1-wire bus
  tft.println("Locating devices");
  tft.print("Found ");
  tft.print(sensors.getDeviceCount(), DEC);
  tft.println(" devices.");
  delay(1000); 
}

////////////////////////////////////////////////

void initTft() {

  // set pin 10 as putput
  pinMode(tft_cs, OUTPUT);

  // If your TFT's plastic wrap has a Black Tab, use the following:
  tft.initR(INITR_BLACKTAB);
  tft.fillScreen(ST7735_BLACK);
  tft.setRotation(3);
  tft.invertDisplay(false);

}

//////////////////////////////////////////////

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

}

///////////////////////////////////////////////

void tftPrintTemp() {

  // sensor blue
  tft.setCursor(45,0);
  tft.setTextColor(ST7735_BLACK);
  tft.print(oldInputData.tempBlue);
  tft.setCursor(45,0);
  tft.setTextColor(ST7735_WHITE);
  tft.print(inputData.tempBlue);

  // sensor brown
  tft.setCursor(45,8);
  tft.setTextColor(ST7735_BLACK);
  tft.print(oldInputData.tempBrown);
  tft.setCursor(45,8);
  tft.setTextColor(ST7735_WHITE);
  tft.print(inputData.tempBrown);

  // sensor water
  tft.setCursor(45,16);
  tft.setTextColor(ST7735_BLACK);
  tft.print(oldInputData.tempWater);
  tft.setCursor(45,16);
  tft.setTextColor(ST7735_WHITE);
  tft.println(inputData.tempWater);

}

///////////////////////////////////////////

void tftPrintTime() {
  t = now();
  if (t != tLast) {
    tLast = t;
    
    dateStringGenerator();
    tft.fillRect(0, 32, 126, 7, ST7735_BLACK);
    tft.setCursor(0,32);
    tft.println(dateString);
  }
}  

