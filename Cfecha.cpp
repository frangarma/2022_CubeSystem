/*
 * Cfecha.cpp
 *
 * Created: 10/03/2018 10:43:42
 *  Author: Fran
 */ 

#include "Cfecha.h"

using namespace std;



Cfecha ::Cfecha()
:year(0), month(0), day(0), dow(0), hour(0), minute(0), second(0)
{
	//Nothing to do for this constructor
}
	
void Cfecha::asignarFecha (uint8_t _year, uint8_t _month, uint8_t _day, uint8_t _dow, uint8_t _hour, uint8_t _minute, uint8_t _second)//used to adjust time completely
{
	year=_year;
	month=_month;
	day=_day;
	dow=_dow;
	hour=_hour;
	minute=_minute;
	second=_second;	
}

uint8_t Cfecha::operator >= (Cfecha const& obj)
{
	if (this->year > obj.year)
	{	
		return 1;
	}
	else if (this->year == obj.year) 
	{
		if (this->month > obj.month)
		{
			return 1;
		}
		else if (this->month == obj.month)
		{
			if (this->day > obj.day)
			{
				return 1;
			}
			else if (this->day == obj.day)
			{
				if (this->hour > obj.hour)
				{
					return 1;
				}
				else if (this->hour == obj.hour)
				{
					if (this->minute > obj.minute)
					{
						return 1;								
					}
					else if(this->minute == obj.minute)
					{
						if(this->second >= obj.second)
						{
							return 1;
						}
					}
					
				}

			}

		}
	}
	return 0;
}

uint8_t Cfecha::operator <= (Cfecha const& obj)
{
	if (this->year < obj.year)
		{	
			return 1;
		}
		else if (this->year == obj.year) 
		{
			if (this->month < obj.month)
			{
				return 1;
			}
			else if (this->month == obj.month)
			{
				if (this->day < obj.day)
				{
					return 1;
				}
				else if (this->day == obj.day)
				{
					if (this->hour < obj.hour)
					{
						return 1;
					}
					else if (this->hour == obj.hour)
					{
						if (this->minute < obj.minute)
						{
							return 1;								
						}
						else if(this->minute == obj.minute)
						{
							if(this->second <= obj.second)
							{
								return 1;
							}
						}

					}

				}

			}
		}
	return 0;
}

uint8_t Cfecha::getSecond() const
{
	return second;
}

uint8_t Cfecha:: getMinute() const
{
	return minute;
}

uint8_t Cfecha:: getHour() const
{
	return hour;
}

uint8_t Cfecha:: getDoW() const
{
	return dow;
}

uint8_t Cfecha:: getDay() const
{
	return day;	
}

uint8_t Cfecha:: getMonth() const
{
	return month;
}

uint8_t Cfecha:: getYear() const
{
	return year;
}

void Cfecha:: setSecond(uint8_t _second)
{
	second=_second;
}

void Cfecha:: setMinute(uint8_t _minute)
{
	minute=_minute;
}

void Cfecha:: setHour(uint8_t _hour)
{
	hour=_hour;
}
void Cfecha::setDay (uint8_t _day)
{
	day=_day;
}
void Cfecha::setDoW (uint8_t _dow)
{
	dow=_dow;
}

void Cfecha:: setMonth(uint8_t _month)
{
	month=_month;
}

void Cfecha:: setYear(uint8_t _year)
{
	year=_year;
}

void Cfecha:: setSecondpp()
{
	second++;
}
void Cfecha:: setMinutepp()
{
	minute++;
}
void Cfecha:: setHourpp()
{
	hour++;
}
void Cfecha:: setDaypp()
{
	day++;
}
void Cfecha:: setMonthpp()
{
	month++;
}
void Cfecha:: setYearpp()
{
	year++;
}
void Cfecha:: setSecondll()
{
	second--;
}
void Cfecha:: setMinutell()
{
	minute--;
}
void Cfecha:: setHourll()
{
	hour--;
}
void Cfecha:: setDayll()
{
	day--;
}
void Cfecha:: setMonthll()
{
	month--;
}
void Cfecha:: setYearll()
{
	year--;
}

uint8_t Cfecha:: compareDates(Cfecha fecha_1, Cfecha fecha_2) {
	
	return 0;//menor
	return 1;//igual
	return 2;//mayor
}

Cfecha Cfecha::addToDateXMinutes(const Cfecha& fecha, uint8_t minutes)
{
	Cfecha dateToReturn;
	uint8_t tempMinutes;
	uint8_t tempHour;
	uint8_t tempDow;
	uint8_t tempDay;
	uint8_t tempMonth;
	uint8_t tempYear;
	dateToReturn = fecha;
	uint8_t hoursToAdd = 0;
	uint8_t minutesToAdd = 0;
	uint8_t totalHours = 0;
	uint8_t totalMinutes = 0;
    
    hoursToAdd = minutes/60;
	minutesToAdd = minutes%60;
	
    totalHours = fecha.getHour() + hoursToAdd;
	totalMinutes = fecha.getMinute() + minutesToAdd;
    if (totalMinutes >= 60)
    {
	    totalHours++;
	    totalMinutes = (totalMinutes -60);
    }
    
	dateToReturn.setMinute(totalMinutes);
	if( totalHours > 23) 
	{
		dateToReturn.setHour( totalHours - 24);
		if(dateToReturn.getDoW() == 7)
		{
			dateToReturn.setDoW(1);
		}
		else
		{
			dateToReturn.setDoW( dateToReturn.getDoW() + 1);
		}
		
		switch(dateToReturn.getMonth())
		{
			// Months with 31 days
			case 1:
			case 3:
			case 5:
			case 7:
			case 8:
			case 10:
			case 12:
				if( (dateToReturn.getDay() == 31 ) )
				{
					dateToReturn.setDay(1);
					if (dateToReturn.getMonth() == 12)
					{
						dateToReturn.setMonth(1);
						dateToReturn.setYearpp();
					}
					else
					{
						dateToReturn.setMonthpp();
					}
				}
				else
				{
					dateToReturn.setDaypp();
				}
				break;
			case 2:
				if( (dateToReturn.getDay() == 28 ) )
				{
					dateToReturn.setDay(1);
					dateToReturn.setMonthpp();
				}
				else
				{
					dateToReturn.setDaypp();
				}
				break;
			case 4:
			case 6:
			case 9:
			case 11:
				if( (dateToReturn.getDay() == 30 ) )
				{
					dateToReturn.setDay(1);
					dateToReturn.setMonthpp();
				}
				else
				{
					dateToReturn.setDaypp();
				}
				break; 
		} //End switch(dateToReturn.getMonth())
	}
    else
    {
        dateToReturn.setHour(totalHours);
    }
	return dateToReturn;
}


