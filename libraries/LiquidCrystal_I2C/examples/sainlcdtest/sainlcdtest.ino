/*
** Example Arduino sketch for SainSmart I2C LCD2004 adapter for HD44780 LCD screens
** Readily found on eBay or http://www.sainsmart.com/ 
** The LCD2004 module appears to be identical to one marketed by YwRobot
**
** Address pins 0,1 & 2 are all permenantly tied high so the address is fixed at 0x27
**
** Written for and tested with Arduino 1.0
** This example uses F Malpartida's NewLiquidCrystal library. Obtain from:
** https://bitbucket.org/fmalpartida/new-liquidcrystal 
**
** Edward Comer
** LICENSE: GNU General Public License, version 3 (GPL-3.0)
**
** NOTE: TEsted on Arduino NANO whose I2C pins are A4==SDA, A5==SCL
*/
#include <Wire.h>
#include <LCD.h>
#include <LiquidCrystal_I2C.h>

int n = 1;

LiquidCrystal_I2C	lcd(0x27);

void setup()
{
  lcd.begin (16,2);
  
// Switch on the backlight
  lcd.setBacklight(HIGH);
  lcd.home ();                   // go home

  lcd.print("TWI-LCD");  
  lcd.setCursor ( 0, 1 );        // go to the 2nd line
  lcd.print("Iteration No: ");
}

void loop()
{
  // Backlight on/off every 3 seconds
  lcd.setCursor (14,1);        // go col 14 of line 3
  lcd.print(n++,DEC);
  lcd.setBacklight(LOW);      // Backlight off
  delay(3000);
  lcd.setBacklight(HIGH);     // Backlight on
  delay(3000);
}

