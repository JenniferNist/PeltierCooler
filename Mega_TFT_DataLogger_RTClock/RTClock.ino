/*
 ** initialize RTClock
 */
void initRTC() {
  //setSyncProvider() causes the Time library to synchronize with the
  //external RTC by calling RTC.get() every five minutes by default.
  setSyncProvider(RTC.get);
  Serial.print("RTC Sync");
  if (timeStatus() != timeSet) Serial.print(" FAIL!");
  Serial.println();
}

/*
** function to set date and time manually over serial monitor
 */
void updateTimeFromSerial() {

  tmElements_t tm;

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


