/* 
* CdadoHora.h
*
* Created: 13/04/2018 16:44:48
* Author: Fran
*/


#ifndef __CDADOHORA_H__
#define __CDADOHORA_H__

#include "Cadc.h"
class CdadoHora : public Cadc {
	//variables
	private:

	//functions
	public:
		CdadoHora ();	
		CdadoHora(const uint8_t _channel);
		~CdadoHora();
		uint8_t valor();
		


}; //CdadoHora

#endif //__CDADOHORA_H__
