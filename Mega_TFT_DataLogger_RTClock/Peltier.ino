/*
** Initialize peltier Control library and define pins
** Set initial intensity and direction to 0
*/
void initPeltier() {
  
  PC.begin();
  // PC.stop();  // needed?  
  
}

/*
** peltier need to cool or heat, 
** depending on the water and target temperatur
** if not set differently, tempTarget is 24C
*/
void peltierControl() {
  
  float tempDifference = inputData.tempWater - inputData.tempTarget;
  
  // tempDifference < 0: water is to cold (20C (tempWater) - 24C (tempTarget) = -4 (tempDifference))
  if (tempDifference < -0.2) {
    peltierInfo.peltierHeating = true;
    peltierInfo.peltierCooling = false;
    if ((tempDifference < -0.2) && (tempDifference >= -0.5)) PC.heat(50);
    if ((tempDifference < -0.5) && (tempDifference >= -1)) PC.heat(75);
    if ((tempDifference < -1) && (tempDifference >= -1.5)) PC.heat(100);
    if ((tempDifference < -1.5) && (tempDifference >= -2)) PC.heat(150);
    if ((tempDifference < -2) && (tempDifference >= -2.5)) PC.heat(200);
    else PC.heat(255);                                                 // max intensity: 255
  }
    
  // tempDifference > 0: water is to warm (27C (tempWater) - 24C (tempTarget) = 3 (tempDifference))
  if (tempDifference > 0.2) {
    peltierInfo.peltierCooling = true;
    peltierInfo.peltierHeating = false;
    if ((tempDifference > 0.2) && (tempDifference <= 0.5)) PC.cool(50);
    if ((tempDifference > 0.5) && (tempDifference <= 1)) PC.cool(75);
    if ((tempDifference > 1) && (tempDifference <= 1.5)) PC.cool(100);
    if ((tempDifference > 1.5) && (tempDifference <= 2)) PC.cool(150);
    if ((tempDifference > 2) && (tempDifference <= 2.5)) PC.cool(200);
    else PC.cool(255);
  }
  
  else {
    peltierInfo.peltierCooling = false;
    peltierInfo.peltierHeating = false;
  }
  
}
