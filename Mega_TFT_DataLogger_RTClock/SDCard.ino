void initSD() {
  errorInitSD = false;
  
  if(!SD.begin(sd_cs)) {
    errorInitSD = true;
  }
  
  tftPrintSDInfo(errorInitSD);
}

///////////////////////////////////////////////////////

void logDataOnSD() {
  
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
    errorTempData();
  } 
} 

