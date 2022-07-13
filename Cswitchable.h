/* 
* File: switchable_h
*
* Created: 18/04/2018 20:10:28
* Author: Fran
*/


#ifndef __SWITCHABLE_H__
#define __SWITCHABLE_H__

// #define _PROGRAMMED		0X01
// #define _UNPROGRAMMED	0X00




#include <stdint.h>


class Cswitchable
{
	//variables
	private:
	uint8_t nOutputpin;
	uint8_t status;// 1 is on 0 off
	char port;
	
	//functions
	public:
	
		Cswitchable();	
		Cswitchable(const uint8_t _nOutputpin, const char _port);
		~Cswitchable();
		void on();
		void off();
		void blink();
		uint8_t stateSwitch();
		void copyStateSwitch(uint8_t);


}; //switchable

#endif //__SWITCHABLE_H__
