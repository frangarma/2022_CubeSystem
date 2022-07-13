/*
 * Clock_DS3231.h
 *
 * Created: 08/03/2018 13:12:58
 *  Author: Fran
 */ 


#ifndef CLOCK_H_
#define CLOCK_H_

#include "Cfecha.h"
#include "Cds3231.h"
#include "Ci2c.h"

//This class aims to isolate Cfecha from the use of hardware directly, in such a way that Cfecha it is used as a base class
//and  Clock derivated from it adding, in Cclock is add an Cds3231 object that are going used to remove the dependency of hardware
//in case of changing the hardware clock ds3231, only would be necessary to change this object.

class Cclock : public Cfecha {
	
	private:
	
		Cds3231 rtc;
		
	public:
		//Cfecha fecha;	
		
		//Constructor
		Cclock();
		~Cclock();		
		uint8_t getSecond();
		uint8_t getMinute();
		uint8_t getHour();
		uint8_t getDoW();
		uint8_t getDate();
		uint8_t getMonth();
		uint8_t getYear();
		void setSecond(uint8_t Second);
		void setMinute(uint8_t Minute);
		void setHour(uint8_t Hour);
		void setDoW(uint8_t DoW);
		void setDate(uint8_t Date);
		void setMonth(uint8_t Month);
		void setYear(uint8_t Year);
		uint8_t getTemperature();
		void asignarFecha(Cfecha fecha, bool setupSecond = false);
		void obtenerFecha(Cfecha& fecha);
		void setDs3231I2cPort(Ci2c*);
};



#endif /* CLOCK_H_ */