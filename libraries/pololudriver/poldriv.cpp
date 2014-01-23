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
 
#include "wiring_private.h"
#include "pins_arduino.h"
#include "poldriv.h"
#include <PWM.h>

 
PD::PD(int pwm, int fw, int rv)
{

	
 	_pwmpin = pwm;
 	_fwpin = fw;
 	_rvpin = rv;

}

void PD::begin() 
{
 	pinMode(_pwmpin, OUTPUT);
 	pinMode(_fwpin, OUTPUT);
 	pinMode(_rvpin, OUTPUT);
 
 	digitalWrite(_rvpin, LOW);
	digitalWrite(_fwpin, LOW);
	analogWrite(_pwmpin, 0);
}

void PD::stop() 
{
 	digitalWrite(_rvpin, LOW);
	digitalWrite(_fwpin, LOW);
	analogWrite(_pwmpin, 0);
}

void PD::forward(int fwSpeed) 
{
	digitalWrite(_rvpin, LOW);
	digitalWrite(_fwpin, HIGH);
	analogWrite(_pwmpin, fwSpeed);
}

void PD::reverse(int rvSpeed) 
{
   	digitalWrite(_fwpin, LOW);
	digitalWrite(_rvpin, HIGH);
	analogWrite(_pwmpin, rvSpeed);
}
