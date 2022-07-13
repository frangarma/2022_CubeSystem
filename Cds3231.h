/* 
* Cds3231.h
*
* Created: 02/07/2020 18:49:22
* Author: fgm97
*/


#ifndef __CDS3231_H__
#define __CDS3231_H__

#include <stdint.h>
#include "Ci2c.h"


#define DS3231_ADDRESS_WRITE	0XD0
#define DS3231_ADDRESS_READ		0XD1
#define DS3231_ADDRESS_SECONDS	0X00
#define DS3231_ADDRESS_MINUTES	0X01
#define DS3231_ADDRESS_HOUR		0X02
#define DS3231_ADDRESS_DoW		0X03	//1-7
#define DS3231_ADDRESS_DATE		0X04	//1-31
#define DS3231_ADDRESS_MONTH	0X05
#define DS3231_ADDRESS_YEAR		0X06	//00-99
#define DS3231_ADDRESS_TEMPERATURE 0X11

class Cds3231
{
	private:
		Ci2c *i2c;

	//functions
	public:
		Cds3231();
		~Cds3231();
		//Cds3231(const Cds3231 &c);
		//Cds3231& operator=( const Cds3231 &c );
		uint8_t getSecond_RTC(void);
		uint8_t getMinute_RTC();
		uint8_t getHour_RTC();
		uint8_t getDoW_RTC();
		uint8_t getDate_RTC();
		uint8_t getMonth_RTC();
		uint8_t getYear_RTC();
		void setSecond_RTC(uint8_t Second);
		void setMinute_RTC(uint8_t Minute);
		void setHour_RTC(uint8_t Hour);
		void setDoW_RTC(uint8_t DoW);
		void setDate_RTC(uint8_t Date);
		void setMonth_RTC(uint8_t Month);
		void setYear_RTC(uint8_t Year);
		uint8_t getTemperature_RTC();
		uint8_t i2cReadFromDS3231 (uint8_t addressRegisterDS3231);
		void i2cWriteToDS3231 (uint8_t addressRegisterDS3231, uint8_t value);
		void setI2cPort(Ci2c*);

		
		//Static members
		static uint8_t bcd_to_decimal(unsigned char d);
		static uint8_t decimal_to_bcd(unsigned char d);




}; //Cds3231

#endif //__CDS3231_H__
