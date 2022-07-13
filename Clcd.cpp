/* 
* Clcd.cpp
*
* Created: 05/07/2020 12:05:04
* Author: fgm97
*/


#include "Clcd.h"

Clcd::Clcd() 
{
}

Clcd::Clcd(Ci2c* i2c)
{
	chipset_lcd= CchipsetLCD(i2c);
} //Clcd

// default destructor
Clcd::~Clcd()
{
} //~Clcd

void Clcd::init(void)
{
	chipset_lcd.init();
	chipset_lcd.clearChipsetMemory();
}

void Clcd::clear(void)
{
	chipset_lcd.clearChipsetMemory();
}

CchipsetLCD* Clcd::getChipsetLcd(void)
{
	return &chipset_lcd;
}

void Clcd::setChipsetI2cPort(Ci2c* i2c)
{
	chipset_lcd.seti2cPort(i2c);
}

