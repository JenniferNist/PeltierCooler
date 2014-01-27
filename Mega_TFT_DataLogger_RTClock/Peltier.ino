/*
** Initialize peltier Control library and define pins
** Set initial intensity and direction to 0
*/
void initPeltier() {
  
  // set pins as output
  PC.begin();       
  //PC.stop();

}

/*
**  
*/
void peltierControl() {
  
  float tempDifference = inputData.tempWater - inputData.tempTarget;
  
  // tempDifference < 0: water is to cold (20C (tempWater) - 24C (tempTarget) = -4 (tempDifference))
  if (tempDifference < 0) {
    if ((tempDifference < 0) && tempDifference >= -1) PC.heat(50);
    if ((tempDifference < -1) && tempDifference >= -2) PC.heat(100);
    if ((tempDifference < -2) && tempDifference >= -3) PC.heat(150);
    if ((tempDifference < -3) && tempDifference >= -4) PC.heat(200);
    else PC.heat(250);                                                 // max intensity: 255
  }
    
  // tempDifference > 0: water is to warm (27C (tempWater) - 24C (tempTarget) = 3 (tempDifference))
  if (tempDifference > 0) {
    if
    
  }
  
}
