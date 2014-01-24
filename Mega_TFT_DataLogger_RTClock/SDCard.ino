void initSD() {
  
  errorInitSD = false;
  tftPrintSDInfo(errorInitSD);
}

///////////////////////////////////////////////////////

void logDataOnSD() {
  
  dataLogStringGenerator(dateString);

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
    errorTempData();
  } 
} 

