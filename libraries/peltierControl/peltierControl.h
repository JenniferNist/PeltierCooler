/*
 * Copyright (c) 2012 by Douwe Bart Mulder <dafmulder@gmail.com>
 * Pololu Driver library (vnh2sp30)
 * Datasheet: http://www.pololu.com/file/0J52/vnh2sp30.pdf
 *
 * This file is free software; you can redistribute it and/or modify
 * it under the terms of either the GNU General Public License version 2
 * or the GNU Lesser General Public License version 2.1, both as
 * published by the Free Software Foundation.
 */

// -----------------------------------------------------------------------------
// Define
// -----------------------------------------------------------------------------
#ifndef peltierControl_h
#define peltierControl_h

// -----------------------------------------------------------------------------
// Enum
// -----------------------------------------------------------------------------
enum PeltierState
{
  PeltierHeating,
  PeltierCooling,
  PeltierStopped
};

// -----------------------------------------------------------------------------
// Class
// -----------------------------------------------------------------------------
class PC 
{
public:
  PC(int pwm, int heating, int cooling, long frequency);
  void begin(); 	
  void stop();
  void heat(int intensity);
  void cool(int intensity);
  
  static PeltierState peltierState;

 private:
  int _pwmPin;
  int _heatingPin;
  int _coolingPin; 
};

// -----------------------------------------------------------------------------
// Variables
// -----------------------------------------------------------------------------

#endif
