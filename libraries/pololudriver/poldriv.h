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
#ifndef poldriv_h
#define poldriv_h

// -----------------------------------------------------------------------------
// Class
// -----------------------------------------------------------------------------
class PD 
{
public:
  PD(int pwm, int fw, int rv);
  void begin(); 	
  void stop();
  void forward(int fwSpeed);
  void reverse(int rvSpeed);
 private:
  int _pwmpin;
  int _fwpin;
  int _rvpin; 
};

// -----------------------------------------------------------------------------
// Variables
// -----------------------------------------------------------------------------


#endif