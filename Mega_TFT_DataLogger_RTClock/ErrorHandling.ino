
void errorTempSensors(boolean, boolean, boolean) {
 tft.setCursor(0,16);
 if(errorBlue) tft.println("No blue termometer");
 if(errorBrown) tft.println("No brown termometer");
 if(errorWater) tft.println("No water termometer");

 while(true);
 //delay(2000); 
}
