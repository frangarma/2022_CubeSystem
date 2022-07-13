/* 
* CdadoDuracion.h
*
* Created: 15/04/2018 18:50:07
* Author: Fran
*/


#ifndef __CDADODURACION_H__
#define __CDADODURACION_H__

#include "Cadc.h"

class CdadoDuracion :public Cadc
{

	private:

//functions
	public:
	CdadoDuracion();
	CdadoDuracion(const uint8_t _channel);
	~CdadoDuracion();
	uint8_t valor();


}; //CdadoDuracion

#endif //__CDADODURACION_H__
