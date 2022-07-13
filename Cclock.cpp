/*
 * Clock_DS3231.cpp
 *
 * Created: 08/03/2018 13:12:42
 *  Author: Fran
 */ 

/*
*New ds3231.cpp using class DS3231
*/

#include "Cclock.h"

//TODO VER SI SON NECESARIOS LOS FIN DE TRANSMICION EN LOS GET, O ESTO SE HA IMPLEMENTADO EN LOS i2c_readAck(), o en este caso el protocolo 12c no lo pide



// Constructor
Cclock::Cclock() : Cfecha() {
	// nothing to do for this constructor.
	rtc = Cds3231();
}

Cclock::~Cclock(){
	
}

// Getter methods
uint8_t Cclock::getSecond() {
	return rtc.getSecond_RTC();
}

uint8_t Cclock::getMinute() {
	return rtc.getMinute_RTC();
}


uint8_t Cclock::getHour() {
	return rtc.getHour_RTC();
}

uint8_t Cclock::getDoW() {
	return rtc.getDoW_RTC();
}

uint8_t Cclock::getDate() {
	return rtc.getDate_RTC();
}

uint8_t Cclock::getMonth() {
	return rtc.getMonth_RTC();
}

uint8_t Cclock::getYear() {
	return rtc.getYear_RTC();
}


uint8_t Cclock::getTemperature() {
	return rtc.getTemperature_RTC();
}

//Setter methods
void Cclock::setSecond(uint8_t Second) {
	rtc.setSecond_RTC(Second);
}

void Cclock::setMinute(uint8_t Minute) {
	rtc.setMinute_RTC(Minute);
}

void Cclock::setHour(uint8_t Hour) {
	rtc.setHour_RTC(Hour);
}

void Cclock::setDoW(uint8_t DoW) {
	rtc.setDoW_RTC(DoW);
}

void Cclock::setDate(uint8_t Date) {
	rtc.setDate_RTC(Date);
}

void Cclock::setMonth(uint8_t Month) {
	rtc.setMonth_RTC(Month);
}

void Cclock::setYear(uint8_t Year) {
	rtc.setYear_RTC(Year);
}

void Cclock:: asignarFecha(Cfecha fecha,  bool setupSecond){
	if (setupSecond)
		setSecond(fecha.getSecond());
 	setMinute(fecha.getMinute());
 	setHour(fecha.getHour());
 	setDoW(fecha.getDoW());
 	setDate(fecha.getDay());
 	setMonth(fecha.getMonth());
 	setYear(fecha.getYear());
}

void Cclock:: obtenerFecha(Cfecha& fecha) {
	fecha.asignarFecha( rtc.getYear_RTC(), rtc.getMonth_RTC(), rtc.getDate_RTC(), rtc.getDoW_RTC(), rtc.getHour_RTC(), rtc.getMinute_RTC(), rtc.getSecond_RTC() );
}



void Cclock::setDs3231I2cPort(Ci2c* i2c)
{
	rtc.setI2cPort(i2c);
}