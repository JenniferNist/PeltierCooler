/*
** check for temperature difference of the two sides of the peltier element
*/
void checkForErrors() {
   
 int tempDifference = abs (inputData.tempBlue - inputData.tempBrown);
  
 // peltier element can not stand to have a temperature difference of over 70C
 if (tempDifference > 70) {
   while (tempDifference > 50) {
     PC.stop();
     pwmWrite(pwmFanPin, 255);
   }
 }
 
  // should any sensor stop working or is not plugged in stop immediatly
  while(inputData.tempBlue <= -85.00 || inputData.tempBrown <= -85.00 || inputData.tempBrown <= -85.00) {
    delay(1000);
    if (inputData.tempBlue <= -85.00 || inputData.tempBrown <= -85.00 || inputData.tempBrown <= -85.00) {
      PC.stop();
      pwmWrite(pwmFanPin, 0);
    }
  }
}
