/* 
* switchable.cpp
*
* Created: 18/04/2018 20:10:27
* Author: Fran
*/


#include "Cswitchable.h"
#include <avr/io.h>

using namespace std;

// default constructor

Cswitchable:: Cswitchable(){
	
}

Cswitchable :: Cswitchable (const uint8_t _nOutputpin, const char _port) 
{
	nOutputpin=_nOutputpin;
	port=_port;	
	off();
} //switchable

// default destructor
Cswitchable :: ~Cswitchable()
{
} //~switchable

void Cswitchable :: on()
{
	if (port=='B') {
		PORTB |= nOutputpin;
	}
	else if (port=='D') {
		PORTD |= nOutputpin;
	}
	status=1;	
}

void Cswitchable :: off()
{
	//	PORTB &= ~nOutputpin;
	if (port=='B') {
		PORTB &= ~nOutputpin;
	}
	else if (port=='D') {
		PORTD &= ~nOutputpin;
	}
	
	status=0;
}

void Cswitchable:: blink()
{
		//#define portx PORTB
		if (port=='B' && nOutputpin== 1) {
			PORTB ^= (1<<PINB0);
		}		
		if (port=='B' && nOutputpin ==2) {
			PORTB ^= (1<<PINB1);
		}
		else if (port=='B' && nOutputpin ==4) {
			PORTB ^= (1<< PINB2);
		}
}

uint8_t Cswitchable::stateSwitch() {
	return status;
}

void Cswitchable ::copyStateSwitch(uint8_t switcActivated) {
	#ifdef DEBUGGER_MODE_R
	sprintf(serialprintdebugger, "p_1");
	UsartTransmitData(serialprintdebugger);
	#endif
	if (switcActivated==1) {
		on();							
	}
	else if (switcActivated==0) 	{
		off();
	}
	 
}