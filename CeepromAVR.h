/* 
* CepromAVR.h
*
* Created: 26/07/2021 17:43:53
* Author: fgm97
*/


#ifndef __CEEPROMAVR_H__
#define __CEEPROMAVR_H__

#include <avr/eeprom.h>
#include "CzonaRiego.h"

class Csistema;

class CeepromAVR
{

	private:
		Csistema* sistema;

	public:
		CeepromAVR();
		CeepromAVR(Csistema*);
		~CeepromAVR();
		void writeZonaRiego(CzonaRiego*);
		CzonaRiego* readZonaRiego(uint8_t numZonaRiego);
		

}; //CepromAVR

#endif //__CEEPROMAVR_H__
