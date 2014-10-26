
/**
 * create string with format "dd.mm.yyyy - hh:mm:ss""
 * for tft
 */
String dateStringGenerator(time_t time) {

  dateString = String("");
  dateString += fillZeros(day(time), 2);
  dateString += ".";
  dateString += fillZeros(month(time), 2);
  dateString += ".";
  dateString += year(time);
  dateString += " - ";
  dateString += fillZeros(hour(time), 2);
  dateString += ":";
  dateString += fillZeros(minute(time), 2);
  dateString += ":";
  dateString += fillZeros(second(time), 2);
  
  return dateString;
}

/**
*  fill heading zeros in strings
*/
String fillZeros(int number, int digits){
  
  char buffer[10];
  char *intStr = itoa(number, buffer, 10);  
  String temp = String(intStr);
  while(temp.length() < digits)
  {
    temp = "0" + temp;
  }
  return temp;
}

/**
 * create string with format "dd,mm,yyyy,hh,mm,ss,tempBlue,tempBrown,tempWater"
 * for data storage on sd-card
 */
String dataLogStringGenerator() {

  // change dateString format to "dd.mm.yyyy,hh.mm.ss"
  String dateStr = dateString;
  dateStr.replace(" - ", " ");
 
  String dataLogString = "";

  dataLogString += floatToString(buffer, inputData.tempWater, 4, 6);
  dataLogString += ";";
  dataLogString += floatToString(buffer, inputData.tempTarget, 4, 6);
  dataLogString += ";";
  dataLogString += String(peltierPwmValue);
  dataLogString += ";";
  dataLogString += floatToString(buffer, inputData.tempBrown, 4, 6);
  dataLogString += ";";
  dataLogString += floatToString(buffer, inputData.tempBlue, 4, 6);
  dataLogString.replace(".",",");
  
  dataLogString = dateStr + ";" + dataLogString;
  return dataLogString;

}

/**
 * create a string from temp data from the buffer array
 * floatToString(buffer string, float value, precision, minimum text width) 
 */
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




