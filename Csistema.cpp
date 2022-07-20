/* 
* Csistema.cpp
*
* Created: 26/06/2020 18:56:20
* Author: fgm97
*/


#include "Csistema.h"

//TODO; Delete  #include "VariablesGlobales.h" only with debug porpouses

#include "VariablesGlobales.h"
#include <stdlib.h>



// default constructor
Csistema::Csistema(uint8_t _numZonas)
{
	numZonas = _numZonas;
	status = standBy;;
	lastStatus = standBy;
	//Chw() initialize by default configuration and peripheral
	hw = Chw();
	clock = Cclock();
	horaActual = Cfecha();
	lcd = Clcd();
	i2csystem = hw.getI2c();
	//Update horaActual from rtc_ds3231
	switch(numZonas)
	{
		case 8:
			zonaRiego[7] = CzonaRiego(this, clock, horaActual, i2csystem, 8, 0x01, 'B');// Decimal correspondence to pin is PINB0
		case 7:
			zonaRiego[6] = CzonaRiego(this, clock, horaActual, i2csystem, 7, 0x01, 'B');// Decimal correspondence to pin is PINB0
		case 6:
			zonaRiego[5] = CzonaRiego(this, clock, horaActual, i2csystem, 6, 0x01, 'B');// Decimal correspondence to pin is PINB0
		case 5:
			zonaRiego[4] = CzonaRiego(this, clock, horaActual, i2csystem, 5, 0x01, 'B');// Decimal correspondence to pin is PINB0
		case 4:
			zonaRiego[3] = CzonaRiego(this, clock, horaActual, i2csystem, 4, 0x01, 'B');// Decimal correspondence to pin is PINB0
		case 3:
			zonaRiego[2] = CzonaRiego(this, clock, horaActual, i2csystem, 3, 0x01, 'B');// Decimal correspondence to pin is PINB0
		case 2:
			zonaRiego[1] = CzonaRiego(this, clock, horaActual, i2csystem, 2, 0x10, 'D');// Decimal correspondence to pin is PIN
		case 1:
			zonaRiego[0] = CzonaRiego(this, clock, horaActual, i2csystem, 1, 0x01, 'B');// Decimal correspondence to pin is PINB0
		break;
	}
	zonaRiego_01 = CzonaRiego(this, clock, horaActual, i2csystem, 1, 0x01, 'B');// Decimal correspondence to pin is PINB0
	zonaRiego_02 = CzonaRiego(this, clock, horaActual, i2csystem, 2, 0x10, 'D');// Decimal correspondence to pin is PIN
	avreeprom = CeepromAVR(this);
} //Csistema

void Csistema::inicializa()
{
	if (hw.getI2c() == 0)
	{
		return;
	}
	lcd.setChipsetI2cPort(i2csystem);
	clock.setDs3231I2cPort(i2csystem);
	refreshDate();
	canvas = Ccanvas(this, &lcd, clock, horaActual);
				
	// Waiting time for power dc to stabilize and get correct init of lcd
	wait_500ms();
	lcd.init();
}

Chw Csistema::damehw()
{
	return this->hw;
}

CzonaRiego* Csistema::getDroppingZone_01(){
	return &zonaRiego_01;
}

CzonaRiego* Csistema::getDroppingZone_02(){
	return &zonaRiego_02;
}

// default destructor
Csistema::~Csistema()
{
} //~Csistema

void Csistema::wait_500ms()
{
	_delay_ms(500);
}

void Csistema::refreshDate(void)
{
	clock.obtenerFecha(horaActual);
}

void Csistema::refreshCanvas(lcdmodes lcdmode)
{
	canvas.refresh(lcdmode);
}

void Csistema::clearLcd(void) 
{
	lcd.clear();
}


void Csistema:: menuScroll(void)
{
	canvas.scroll_throug_menu();
}
void Csistema:: modeProgramming(void)
{
	canvas.enter_programming_mode();
}

void Csistema:: debug(int veces)
{
	for (int i=0;i< (veces*2);i++) 
	{	
		led_activity.blink();
		led_fail.blink();
		_delay_ms(100);		 
 	}
	 _delay_ms(500);
}

Cfecha Csistema::getDate(void)
{
	return this->horaActual;
}

void Csistema::setStatus(systemStatus _status)
{
	lastStatus = this->status;
	status = _status;
}
Csistema::systemStatus Csistema::getStatus()
{
	return status;
}

Csistema::systemStatus Csistema::getLastStatus()
{
	return lastStatus;
}

CeepromAVR* Csistema::getAvrEeprom()
{
	return &avreeprom;
}
