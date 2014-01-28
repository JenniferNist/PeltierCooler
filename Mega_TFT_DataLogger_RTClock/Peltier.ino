/*
** Initialize peltier Control library and define pins
** Set initial intensity and direction to 0
*/
void initPeltier() {
  
  PC.begin();
  
}

/*
** peltier need to cool or heat, 
** depending on the water and target temperatur
** if not set differently, tempTarget is 24C
*/
void peltierControl() {
  
  oldPeltierInfo = peltierInfo;
  float tempDifference = inputData.tempWater - inputData.tempTarget;
  int intensity = 0;
  
  // tempDifference < 0: water is to cold (20C (tempWater) - 24C (tempTarget) = -4 (tempDifference))
  if (tempDifference < -0.2) {
    
    peltierInfo.peltierHeating = true;
    peltierInfo.peltierCooling = false;
    
    // set intensity of peltier depending on the temperature difference
    intensity = map(tempDifference, -0.2, -2.5, 0, 255);
    PC.heat(intensity);
    if (tempDifference < -2.5) PC.heat(255);       // max intensity: 255
  }
    
  // tempDifference > 0: water is to warm (27C (tempWater) - 24C (tempTarget) = 3 (tempDifference))
  if (tempDifference > 0.2) {
    
    peltierInfo.peltierHeating = false;
    peltierInfo.peltierCooling = true;
    
    // set intensity of peltier depending on the temperature difference
    intensity = map(tempDifference, 0.2, 2.5, 0, 255);
    PC.cool(intensity);
    if (tempDifference > 2.5) PC.cool(255);
  }
  
  else {
    peltierInfo.peltierCooling = false;
    peltierInfo.peltierHeating = false;

    }
}
