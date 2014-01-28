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
  
  float tempDifference = inputData.tempWater - inputData.tempTarget;
  
  // tempDifference < 0: water is to cold (20C (tempWater) - 24C (tempTarget) = -4 (tempDifference))
  if (tempDifference < -0.2) {
    
    // check wether the peltier was cooling before
    // cooling: heating = false, cooling = true)
    // set mode changed flag as true
    if (!peltierInfo.peltierHeating && peltierInfo.peltierCooling) {
      peltierInfo.peltierHeating = true;
      peltierInfo.peltierCooling = false;
      peltierInfo.peltierChangeMode = true;
    }
    // check wether the peltier was off before
    // off: heating = false, cooling = false
    // set mode changed flag as true
    if (!peltierInfo.peltierHeating && !peltierInfo.peltierCooling {
      peltierInfo.peltierHeating = true;
      peltierInfo.peltierChangeMode = true;
    }
    // if nothing changed, set the change mode falg as false
    else {
      peltierInfo.peltierChangeMode = false;
    }
    
    // set intensity of peltier depending on the temperature difference
    if ((tempDifference < -0.2) && (tempDifference >= -0.5)) PC.heat(50);
    if ((tempDifference < -0.5) && (tempDifference >= -1)) PC.heat(75);
    if ((tempDifference < -1) && (tempDifference >= -1.5)) PC.heat(100);
    if ((tempDifference < -1.5) && (tempDifference >= -2)) PC.heat(150);
    if ((tempDifference < -2) && (tempDifference >= -2.5)) PC.heat(200);
    else PC.heat(253);           // max intensity: 255
  }
    
  // tempDifference > 0: water is to warm (27C (tempWater) - 24C (tempTarget) = 3 (tempDifference))
  if (tempDifference > 0.2) {
    
    // check wether the peltier was heating before
    // heating: heating = true, cooling = false)
    // set mode changed flag as true
    if (peltierInfo.peltierHeating && !peltierInfo.peltierCooling) {
      peltierInfo.peltierHeating = false;
      peltierInfo.peltierCooling = true;
      peltierInfo.peltierChangeMode = true;
    }
    // check wether the peltier was off before
    // off: heating = false, cooling = false
    // set mode changed flag as true
    if (!peltierInfo.peltierHeating && !peltierInfo.peltierCooling {
      peltierInfo.peltierCooling = true;
      peltierInfo.peltierChangeMode = true;
    }
    // if nothing changed, set the change mode falg as false
    else {
      peltierInfo.peltierChangeMode = false;
    }
    
    // set intensity of peltier depending on the temperature difference
    if ((tempDifference > 0.2) && (tempDifference <= 0.5)) PC.cool(50);
    if ((tempDifference > 0.5) && (tempDifference <= 1)) PC.cool(75);
    if ((tempDifference > 1) && (tempDifference <= 1.5)) PC.cool(100);
    if ((tempDifference > 1.5) && (tempDifference <= 2)) PC.cool(150);
    if ((tempDifference > 2) && (tempDifference <= 2.5)) PC.cool(200);
    else PC.cool(253);
  }
  
  else {
    // peltier if off
    // if peltier was cooling or heating before
    if (peltierInfo.peltierHeating || peltierInfo.peltierCooling) {
      peltierInfo.peltierCooling = false;
      peltierInfo.peltierHeating = false;
      peltierInfo.peltierChangeMode = true;
    }
    // if nothing changed, set the change mode falg as false
    else {
      peltierInfo.peltierChangeMode = false;
    }
  }
  
}
