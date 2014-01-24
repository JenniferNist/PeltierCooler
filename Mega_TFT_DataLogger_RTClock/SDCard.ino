void initSD() {

  tft.println("Initializing SD card...");

  if (!SD.begin(sd_cs)) {
    tft.println("initialization failed!");
    while(true);
    return;
  }
  tft.println("initialization done.");

}

///////////////////////////////////////////////////////

void logTemp() {

  // open the file. note that only one file can be open at a time,
  // so you have to close this one before opening another.
  File dataFile = SD.open("tempData.txt", FILE_WRITE);
  dataLogStringGenerator(dateString);

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

