/*
 * SD card attached to SPI bus as follows:
 ** MOSI - pin 51
 ** MISO - pin 50
 ** CLK - pin 52
 ** SD CS - pin 49 
 */

#include <Adafruit_GFX.h>    // Core graphics library
#include <Adafruit_ST7735.h> // Hardware-specific library
#include <SD.h>
#include <SPI.h>
#include <OneWire.h>
#include <DallasTemperature.h>

#include <DS3232RTC.h>        //http://github.com/JChristensen/DS3232RTC
#include <Time.h>             //http://playground.arduino.cc/Code/Time
#include <Wire.h>             //http://arduino.cc/en/Reference/Wire



// For the breakout, you can use any (2 or) 3 pins
#define tft_cs   53
#define dc   48
#define rst  -1  // you can also connect this to the Arduino reset
#define sd_cs 49

// Data wire is plugged into port 40 on the Arduino
#define ONE_WIRE_BUS 40
#define TEMPERATURE_PRECISION 12

typedef struct inputDataType{
  float tempBlue;
  float tempBrown;
  float tempWater;
  float tempTarget;
};

inputDataType inputData;
inputDataType oldInputData;

/////////////////////////////////////////////////////////


// Setup a oneWire instance to communicate with any OneWire devices (not just Maxim/Dallas temperature ICs)
OneWire oneWire(ONE_WIRE_BUS);

// Pass our oneWire reference to Dallas Temperature. 
DallasTemperature sensors(&oneWire);

// arrays to hold device addresses
DeviceAddress blueTermometer, brownTermometer, waterTermometer;

// in case of an error
boolean errorState = false;

Adafruit_ST7735 tft = Adafruit_ST7735(tft_cs, dc, rst);

static time_t tLast;
time_t t;
tmElements_t tm;

File myFile;
String dateString = "";

//////////////////////////////////////////////////////////


void setup()
{
  // Open serial communications and wait for port to open:
  Serial.begin(115200);
  sensors.begin();

  initRTC();
  initTempSensors();
  initTft();
  initSD();
  delay(2000);

  locateTempSensors();
  writeStaticText();

}


//////////////////////////////////////////////////////////////

void loop()
{
  updateTimeFromSerial();
  getTemp();
  tftPrintTime();
  tftPrintTemp();
  logTemp();
}




///////////////////////////////////////////////////////////////
            /// Functions ////
///////////////////////////////////////////////////////////////

void initRTC() {
    //setSyncProvider() causes the Time library to synchronize with the
    //external RTC by calling RTC.get() every five minutes by default.
    setSyncProvider(RTC.get);
    Serial.print("RTC Sync");
    if (timeStatus() != timeSet) Serial.print(" FAIL!");
    Serial.println();
}

///////////////////////////////////////////////////////////////

void initTempSensors() {

  // set the resolution
  sensors.setResolution(blueTermometer, TEMPERATURE_PRECISION);
  sensors.setResolution(brownTermometer, TEMPERATURE_PRECISION);
  sensors.setResolution(waterTermometer, TEMPERATURE_PRECISION);

  inputData.tempBlue = 0;
  inputData.tempBrown = 0;
  inputData.tempWater = 0;
  inputData.tempTarget = 24;

}

////////////////////////////////////////////////////////////
void initTft() {

  // set pin 10 as putput
  pinMode(tft_cs, OUTPUT);

  // If your TFT's plastic wrap has a Black Tab, use the following:
  tft.initR(INITR_BLACKTAB);
  tft.fillScreen(ST7735_BLACK);
  tft.setRotation(3);
  tft.invertDisplay(false);

}

///////////////////////////////////////////////////////////////

void initSD() {

  tft.println("Initializing SD card...");

  if (!SD.begin(sd_cs)) {
    tft.println("initialization failed!");
    while(true);
    return;
  }
  tft.println("initialization done.");

}

/////////////////////////////////////////////////////////////////

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


///////////////////////////////////////////////////////////////////

void updateTimeFromSerial() {
      //check for input to set the RTC, minimum length is 12, i.e. yy,m,d,h,m,s
    if (Serial.available() >= 12) {
        //note that the tmElements_t Year member is an offset from 1970,
        //but the RTC wants the last two digits of the calendar year.
        //use the convenience macros from Time.h to do the conversions.
        int y = Serial.parseInt();
        if (y >= 100 && y < 1000)
            Serial.println("Error: Year must be two digits or four digits!");
        else {
            if (y >= 1000)
                tm.Year = CalendarYrToTm(y);
            else    //(y < 100)
                tm.Year = y2kYearToTm(y);
            tm.Month = Serial.parseInt();
            tm.Day = Serial.parseInt();
            tm.Hour = Serial.parseInt();
            tm.Minute = Serial.parseInt();
            tm.Second = Serial.parseInt();
            t = makeTime(tm);
            RTC.write(tm);
            setTime(t);        
            Serial.print("RTC set to: ");
            Serial.println(dateString);
            //dump any extraneous input
            while (Serial.available() > 0) Serial.read();
        }
    }
} 

////////////////////////////////////////////////////////////////////

void getTemp() {

  oldInputData = inputData;

  // call sensors.requestTemperatures() to issue a global temperature 
  // request to all devices on the bus
  sensors.requestTemperatures();
  inputData.tempBlue = sensors.getTempC(blueTermometer);
  inputData.tempBrown = sensors.getTempC(brownTermometer);
  inputData.tempWater = sensors.getTempC(waterTermometer);

}

//////////////////////////////////////////////////////////////////

void tftPrintTime() {
      t = now();
    if (t != tLast) {
        tLast = t;
        
        dateString = String(day(t));
        dateString += ".";
        dateString += month(t); 
        dateString += ".";
        dateString += year(t);
        dateString += " - ";
        dateString += hour(t);
        dateString += ":";
        dateString += minute(t);
        dateString += ":";
        dateString += second(t);

        tft.fillRect(0, 32, 126, 7, ST7735_BLACK);
        tft.setCursor(0,32);
        tft.println(dateString);
    }
}  

//////////////////////////////////////////////////////////////////

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

/////////////////////////////////////////////////////////

void locateTempSensors() {
  
  tft.setCursor(0,0);
  tft.fillScreen(ST7735_BLACK);
  // locate devices on the 1-wire bus
  tft.println("Locating devices");
  tft.print("Found ");
  tft.print(sensors.getDeviceCount(), DEC);
  tft.println(" devices.");
  delay(1000);

  // debug output if no sensors could be found
  if (!sensors.getAddress(blueTermometer, 0)) {
    tft.println("No blue termometer");
    errorState = true; 
  }
  if (!sensors.getAddress(brownTermometer, 2)) {
    tft.println("No brown termometer");
    errorState = true;
  } 
  if (!sensors.getAddress(waterTermometer, 1)) {
    tft.println("No water termometer");
    errorState = true;
  }   

  // in case of an error blog the program from starting
  if (errorState) {
    while (true);
  }

  delay(1000);
}

////////////////////////////////////////////////////////////

void logTemp() {

  // read three sensors and append to the string:
  char buffer[40];
  String dateStr = dateString;

  //floatToString(buffer string, float value, precision, minimum text width)  
  // make a string for assembling the data to log  
  String dataLogString = "";
  dateStr.replace(".", ",");
  dateStr.replace(":", ",");
  dateStr.replace(" - ", ",");
  dataLogString = dateStr;
  dataLogString += ",";
  dataLogString += floatToString(buffer, inputData.tempBlue, 4, 6);
  dataLogString += ",";
  dataLogString += floatToString(buffer, inputData.tempBrown, 4, 6);
  dataLogString += ",";
  dataLogString += floatToString(buffer, inputData.tempWater, 4, 6);

  // open the file. note that only one file can be open at a time,
  // so you have to close this one before opening another.
  File dataFile = SD.open("tempData.txt", FILE_WRITE);

  // if the file is available, write to it:
  if (dataFile) {
    dataFile.println(dataLogString);
    dataFile.close();
  }  
  // if the file isn't open, pop up an error:
  else {
    tft.println("error opening tempData.txt");
    while (true);
  } 
} 

///////////////////////////////////////////////////////////

char * floatToString(char * outstr, double val, byte precision, byte widthp){
  char temp[16]; //increase this if you need more digits than 15
  byte i;

  temp[0]='\0';
  outstr[0]='\0';

  if(val < 0.0){
    strcpy(outstr,"-\0");  //print "-" sign
    val *= -1;
  }

  if( precision == 0) {
    strcat(outstr, ltoa(round(val),temp,10));  //prints the int part
  }
  else {
    unsigned long frac, mult = 1;
    byte padding = precision-1;

    while (precision--)
      mult *= 10;

    val += 0.5/(float)mult;      // compute rounding factor

    strcat(outstr, ltoa(floor(val),temp,10));  //prints the integer part without rounding
    strcat(outstr, ".\0"); // print the decimal point

    frac = (val - floor(val)) * mult;

    unsigned long frac1 = frac;

    while(frac1 /= 10) 
      padding--;

    while(padding--) 
      strcat(outstr,"0\0");    // print padding zeros

    strcat(outstr,ltoa(frac,temp,10));  // print fraction part
  }

  // generate width space padding 
  if ((widthp != 0)&&(widthp >= strlen(outstr))){
    byte J=0;
    J = widthp - strlen(outstr);

    for (i=0; i< J; i++) {
      temp[i] = ' ';
    }

    temp[i++] = '\0';
    strcat(temp,outstr);
    strcpy(outstr,temp);
  }

  return outstr;
}

