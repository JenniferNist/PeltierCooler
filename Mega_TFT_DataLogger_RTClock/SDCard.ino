/**
 * initialize sd-card
 * set flag, wether sd-card was found or not
 */
void initSD() {

  if(!SD.begin(sd_cs)) {
    errorFlag.errorInitSD = true;
  }
}

time_t oldTime = 0;
/**
 * create dataLogString
 * open (and create if its not existing) log file
 * write information (date and temperature of each sensor) in  log file
 * call error function in case file couldn't be opend (created)
 */
void logDataOnSD() {

  if ((currentTime - 2) < oldTime) {
    return;
  }
  oldTime= currentTime;
  
  dataLogString = dataLogStringGenerator();
  // open the file. note that only one file can be open at a time,
  // so you have to close this one before opening another.
  
  boolean fileExists = SD.exists("tempData.csv");
  
  File dataFile = SD.open("tempData.csv", FILE_WRITE);

  // if the file is available, write to it:
  if (dataFile) { 
    
    if(!fileExists) {
      dataFile.println("Datum und Uhrzeit;Wassertemperatur;Zieltemperatur;Peltier Leistung;Peltiertemperatur (oben);Peltiertemperatur (unten)"); 
    }
    dataFile.println(dataLogString);
    dataFile.flush();
    dataFile.close();
  }  
  // if the file isn't open, pop up an error:
  else {
    errorFlag.errorTempData = true;
  } 
} 



