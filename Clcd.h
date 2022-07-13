/* 
* Clcd.h
*
* Created: 05/07/2020 12:05:04
* Author: fgm97
*/


#ifndef __CLCD_H__
#define __CLCD_H__

#include "CchipsetLCD.h"
class Ci2c;

class Clcd
{
	//variables
	public:
	protected:
	private:
		CchipsetLCD chipset_lcd;

	//functions
	public:
		Clcd();
		Clcd(Ci2c*);
		~Clcd();
		void init(void);
		void clear(void);
		CchipsetLCD* getChipsetLcd(void);
		void setChipsetI2cPort(Ci2c*);

	protected:
	private:
		//Clcd( const Clcd &c );
		//Clcd& operator=( const Clcd &c );

}; //Clcd

#endif //__CLCD_H__
