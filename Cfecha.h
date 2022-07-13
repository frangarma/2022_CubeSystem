/*
 * Cfecha.h
 *
 * Created: 10/03/2018 10:44:01
 *  Author: Fran
 */ 


#ifndef CFECHA_H_
#define CFECHA_H_

#include "stdint.h"

class Cfecha
{
	protected: // It is used in the daughter class DS3231
		uint8_t year, month, day, dow, hour, minute, second;	
	
	public:
		Cfecha();
		void asignarFecha (uint8_t _year, uint8_t _month, uint8_t _day, uint8_t _dow, uint8_t _hour, uint8_t _minute, uint8_t _second);//used to adjust time completely
		uint8_t operator >= (Cfecha const&);
		uint8_t operator <= (Cfecha const&);
		uint8_t getSecond() const;
		uint8_t getMinute() const;
		uint8_t getHour() const;
		uint8_t getDoW() const;
		uint8_t getDay() const;
		uint8_t getMonth() const;
		uint8_t getYear() const;	
		void setSecond(uint8_t _second);
		void setMinute(uint8_t _minute);
		void setHour(uint8_t _hour);
		void setDay(uint8_t _day);
		void setDoW (uint8_t _dow);
		void setMonth(uint8_t _month);
		void setYear(uint8_t _year);			
		void setSecondpp();
		void setMinutepp();
		void setHourpp();
		void setDaypp();
		void setMonthpp();
		void setYearpp();
		void setSecondll();
		void setMinutell();
		void setHourll();
		void setDayll();
		void setMonthll();
		void setYearll();
		//TODO, Implementation pending
		uint8_t compareDates(Cfecha, Cfecha);

		/**
		 * @Brief: This method aims to get a Cfecha object then of adding a xx minutes
		 * @param: Cfecha fecha
		 * @param: uint8_t minutes
		 * @return: Cfecha
		 */
		Cfecha addToDateXMinutes(const Cfecha&, uint8_t);
	
};


#endif /* CFECHA_H_ */