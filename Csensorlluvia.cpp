/* 
* Csensorlluvia.cpp
*
* Created: 20/10/2018 19:31:28
* Author: Fran
*/


#include "Csensorlluvia.h"
#include "Cbsp.h"
#include "definiciones.h"

// default constructor
Csensorlluvia::Csensorlluvia()
{
} //Csensorlluvia

// default destructor
Csensorlluvia::~Csensorlluvia()
{
} //~Csensorlluvia

Csensorlluvia::Csensorlluvia (const uint8_t _channel) : Cadc (_channel){
	
}

uint8_t Csensorlluvia :: valor(){
	uint16_t x=read(), r;
	if (x==1023) { r=0; } // avoid 0 division
	else { r= ( referenceResistor / ((1023.0/x)-1) ); } // r is the resistor value in ohm
	//TODO, Terminar la implementación del algoritmo
	return (uint8_t)r;
}