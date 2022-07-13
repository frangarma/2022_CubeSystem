/* 
* Cds3231.cpp
*
* Created: 02/07/2020 18:49:22
* Author: fgm97
*/


#include "Cds3231.h"



// default constructor
Cds3231::Cds3231()
{
	//i2c = &Ci2c();
} //Cds3231

// default destructor
Cds3231::~Cds3231()
{
} //~Cds3231


uint8_t Cds3231::getSecond_RTC(void){
	return i2cReadFromDS3231(DS3231_ADDRESS_SECONDS);
	//TODO, Convert i2c into class to make things like, it would be necessary to create an object i2c inside Cds3231
	//i2c.readfromds2131(DS3231_ADDRESS_SECONDS)
}


uint8_t Cds3231::getMinute_RTC() {
	return i2cReadFromDS3231(DS3231_ADDRESS_MINUTES);
}


uint8_t Cds3231::getHour_RTC() {
	return i2cReadFromDS3231(DS3231_ADDRESS_HOUR);
}

uint8_t Cds3231::getDoW_RTC() {
	return i2cReadFromDS3231(DS3231_ADDRESS_DoW);
}

uint8_t Cds3231::getDate_RTC() {
	return i2cReadFromDS3231(DS3231_ADDRESS_DATE);
}

uint8_t Cds3231::getMonth_RTC() {
	return i2cReadFromDS3231(DS3231_ADDRESS_MONTH);
}

uint8_t Cds3231::getYear_RTC() {
	return i2cReadFromDS3231(DS3231_ADDRESS_YEAR);
}


uint8_t Cds3231::getTemperature_RTC() {
	// Checks the internal thermometer on the DS3231 and returns the
	// temperature as a floating-point value.

	// Updated / modified a tiny bit from "Coding Badly" and "Tri-Again"
	// http://forum.arduino.cc/index.php/topic,22301.0.html
	
	// 	uint8_t tMSB, tLSB;
	// 	uint8_t temp3231;
	
	// temp registers (11h-12h) get updated automatically every 64s
	i2c->start(DS3231_ADDRESS_WRITE);
	i2c->write(DS3231_ADDRESS_TEMPERATURE);// set next input to start at the seconds register
	i2c->start(DS3231_ADDRESS_READ);
	return i2c->readAck();//Lee el registro 11, contiene la T� con bit 7 bit signo, 0 positivo 1 negativo
	// tMSB = i2c_readAck(); //2's complement int portion
	// 	tLSB = i2c_readAck(); //fraction portion
	// 	temp3231 = ((((short)tMSB << 8) | (short)tLSB) >> 6) / 4.0;
	//  return temp3231;
	// 	temp3231 = i2c_readAck()<< 8;
	// 	temp3231|= i2c_readAck();
	// 	return temp3231/25
}

void Cds3231::setSecond_RTC(uint8_t Second) {
	i2cWriteToDS3231(DS3231_ADDRESS_SECONDS, Second);
}

void Cds3231::setMinute_RTC(uint8_t Minute) {
	i2cWriteToDS3231(DS3231_ADDRESS_MINUTES, Minute);
}

void Cds3231::setHour_RTC(uint8_t Hour) {
	i2cWriteToDS3231(DS3231_ADDRESS_HOUR, Hour);
}

void Cds3231::setDoW_RTC(uint8_t DoW) {
	i2cWriteToDS3231(DS3231_ADDRESS_DoW, DoW);
}

void Cds3231::setDate_RTC(uint8_t Date) {
	i2cWriteToDS3231(DS3231_ADDRESS_DATE, Date);
}

void Cds3231::setMonth_RTC(uint8_t Month) {
	i2cWriteToDS3231(DS3231_ADDRESS_MONTH, Month);
}

void Cds3231::setYear_RTC(uint8_t Year) {
	i2cWriteToDS3231(DS3231_ADDRESS_YEAR, Year);
}



uint8_t Cds3231::decimal_to_bcd(unsigned char d) {
	return (((d / 10) << 4) & 0xF0) | ((d % 10) & 0x0F);
}


uint8_t Cds3231::i2cReadFromDS3231 (uint8_t addressRegisterDS3231) {
	i2c->start(DS3231_ADDRESS_WRITE);
	i2c->write(addressRegisterDS3231);// set next input to start at the seconds register
	i2c->start(DS3231_ADDRESS_READ);
	return bcd_to_decimal(i2c->readAck());
}

void Cds3231::i2cWriteToDS3231 (uint8_t addressRegisterDS3231, uint8_t value) {
	i2c->start(DS3231_ADDRESS_WRITE);
	i2c->write(addressRegisterDS3231);// set next input to start at the seconds register
	i2c->write(decimal_to_bcd(value));
	i2c->stop();
}

//used to get_hour/min/sec functions
uint8_t Cds3231:: bcd_to_decimal(unsigned char d) {
	return ((d & 0x0F) + (((d & 0xF0) >> 4) * 10));
}

void Cds3231::setI2cPort(Ci2c* i2c)
{
	this->i2c = i2c;
}
