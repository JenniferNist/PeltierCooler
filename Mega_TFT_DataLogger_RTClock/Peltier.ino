/**
 * Initialize peltier Control library and define pins
 * Set initial intensity and direction to 0
 */
void initPeltier() {
  
  PC.begin();
}

/**
 * peltier need to cool or heat, 
 * depending on the water and target temperatur
 * if not set differently, tempTarget is 24C
 */
void peltierControl() {

  int tempDifference = (inputData.tempWater - inputData.tempTarget) * 10;

  // tempDifference < 0: water is to cold (20C (tempWater) - 24C (tempTarget) = -4 (tempDifference))
  if ((PeltierCooling && tempDifference < -2) || (PeltierStopped && tempDifference < -5)) {
    // set intensity of peltier depending on the temperature difference
    // positive for heating the water.
    peltierPwmValue = map(abs(tempDifference), 2, 25, 0, 255);
    
    if (peltierPwmValue > 255) {
      peltierPwmValue = 255;
    }
    
    PC.heat(peltierPwmValue);
  }

  // tempDifference > 0: water is to warm (27C (tempWater) - 24C (tempTarget) = 3 (tempDifference
  else if ((PeltierHeating && tempDifference > 2) || (PeltierStopped && tempDifference > 5)) {
    // set intensity of peltier depending on the temperature difference
    // negative for cooling the water.
    peltierPwmValue = (map(tempDifference, 2, 25, 0, 255)* (-1));
    
    if (peltierPwmValue < -255) {
      peltierPwmValue = -255;
    }
    
    PC.cool(abs(peltierPwmValue));
  }

  else if ((tempDifference <= 2) && (tempDifference >= -2)) {
    // Set the Peltier to idle mode.
    peltierPwmValue = 0;
    PC.stop(); 
  }
}

