/*
** initialize sd-card
 ** set flag, wether sd-card was found or not
 */
void initSD() {

  if(!SD.begin(sd_cs)) {
    errorFlag.errorInitSD = true;
  }
}

/*
** create dataLogString
 ** open (and create if its not existing) log file
 ** write information (date and temperature of each sensor) in  log file
 ** call error function in case file couldn't be opend (created)
 */
void logDataOnSD() {

  dataLogStringGenerator();

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
    errorFlag.errorTempData = true;
  } 
} 


