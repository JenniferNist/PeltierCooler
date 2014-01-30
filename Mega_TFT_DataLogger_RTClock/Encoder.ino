/**
 *
 */
void initEncoder() {
  
  // load float from eeprom(last set temperature value)
  myEnc.write((long)(eeprom_read_float(0)*40));
  pinMode(encoderTamper, INPUT_PULLUP);
  
}

float oldPosition  = -999;
float rawTarget = 0;

/**
 * target temperature (tempTarget) is changable by Encoder
 */
void setTempTarget() {
  
  
  
  long newPosition = myEnc.read() / 4;
  if (newPosition != oldPosition) {
    

    
    oldPosition = newPosition;
    rawTarget =  (newPosition/10.0);
    if (rawTarget > maxTemperature) {
      myEnc.write((long)(maxTemperature*40));
      rawTarget = maxTemperature;
    }
    if (rawTarget < minTemperature) {
      myEnc.write((long)(minTemperature*40));
      rawTarget = minTemperature;
    }
    Serial.println(rawTarget);
  }
  
  
  if (digitalRead(encoderTamper) == LOW) {
    eeprom_write_float(0, rawTarget);
    Serial.println("Value written:");
    Serial.println(eeprom_read_float(0));
    delay(1000);
  }

  inputData.tempTarget = rawTarget;

}



