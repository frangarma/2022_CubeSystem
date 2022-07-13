/* 
* Cprogramador.cpp
*
* Created: 20/10/2018 11:36:50
* Author: Fran
*/


#include "Cprogramador.h"



// default constructor
Cprogramador::Cprogramador()
{
} //Cprogramador

// default destructor
Cprogramador::~Cprogramador()
{
} //~Cprogramador

Cprogramador::Cprogramador (uint8_t _num_zonasRiego, uint8_t _offset_activated, uint8_t _sensorLluvia_activated) {
	num_zonasRiego=_num_zonasRiego;
	offset_activated=_offset_activated;
	sensorLluvia_activated=_sensorLluvia_activated;
	sensorlluvia= Csensorlluvia(4);//TODO, ver como está el canal 4 del adc
	
}