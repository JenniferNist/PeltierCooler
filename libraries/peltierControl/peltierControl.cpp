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
#include "peltierControl.h"
#include "PWM.h"

PeltierState PC::peltierState = PeltierStopped;
 
PC::PC(int pwm, int heating, int cooling, long frequency)
{

 	_pwmPin = pwm;
 	_heatingPin = heating;
 	_coolingPin = cooling;
	SetPinFrequencySafe(pwm, frequency);
	peltierState = PeltierStopped;
}

void PC::begin() 
{
 	pinMode(_pwmPin, OUTPUT);
 	pinMode(_heatingPin, OUTPUT);
 	pinMode(_coolingPin, OUTPUT);
	peltierState = PeltierStopped; 
	stop();
}

void PC::stop() 
{
 	digitalWrite(_coolingPin, LOW);
	digitalWrite(_heatingPin, LOW);
	pwmWrite(_pwmPin, 0);
	peltierState = PeltierStopped;
}

void PC::heat(int intensity) 
{
	digitalWrite(_coolingPin, LOW);
	digitalWrite(_heatingPin, HIGH);
	pwmWrite(_pwmPin, intensity);
	peltierState = PeltierHeating;
}

void PC::cool(int intensity) 
{
   	digitalWrite(_heatingPin, LOW);
	digitalWrite(_coolingPin, HIGH);
	pwmWrite(_pwmPin, intensity);
	peltierState = PeltierCooling;
}
