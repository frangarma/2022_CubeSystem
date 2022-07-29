/* 
* CdadoDuracion.cpp
*
* Created: 15/04/2018 18:50:07
* Author: Fran
*/


#include "CdadoDuracion.h"
#include <stdio.h>
#include "definiciones.h"
#include "Cbsp.h"
#include "VariablesGlobales.h"

// default constructor

CdadoDuracion ::CdadoDuracion () :Cadc () {
	
}

CdadoDuracion::CdadoDuracion (const uint8_t _channel) : Cadc (_channel)
{
} //CdadoDuracion

// default destructor
CdadoDuracion::~CdadoDuracion()
{
} //~CdadoDuracion

uint8_t CdadoDuracion :: valor () {
	
	uint16_t x=read(), r;
	uint8_t i=0; // j=0, encontrado=0;
	if (x==1023) { r=0; } // avoid 0 division
	else { r= ( referenceResistor / ((1023.0/x)-1) ); } // r is the resistor value in ohm
	#ifdef DEBUGGER_MODE_R
		sprintf(serialprintdebugger, "%d,", r);
		UsartTransmitData(serialprintdebugger);
	#endif
	if      ((r >= (arrayValoresResistor[0]-toleranceenohmLecturasResistor)) && ( r <= (arrayValoresResistor[0]+toleranceenohmLecturasResistor))) { i=0; }
	else if ((r >= (arrayValoresResistor[1]-toleranceenohmLecturasResistor)) && ( r <= (arrayValoresResistor[1]+toleranceenohmLecturasResistor))) { i=1; }
	else if ((r >= (arrayValoresResistor[2]-toleranceenohmLecturasResistor)) && ( r <= (arrayValoresResistor[2]+toleranceenohmLecturasResistor))) {	i=2; }
	else if ((r >= (arrayValoresResistor[3]-toleranceenohmLecturasResistor)) && ( r <= (arrayValoresResistor[3]+toleranceenohmLecturasResistor))) {	i=3; }
	else if ((r >= (arrayValoresResistor[4]-toleranceenohmLecturasResistor)) && ( r <= (arrayValoresResistor[4]+toleranceenohmLecturasResistor))) {	i=4; }
	else if ((r >= (arrayValoresResistor[5]-toleranceenohmLecturasResistor)) && ( r <= (arrayValoresResistor[5]+toleranceenohmLecturasResistor))) {	i=5; }
	else i=100;// Caso para el default
	
	#ifdef DEBUGGER_MODE
		sprintf(serialprintdebugger, "case_m=%d \r", i);
		UsartTransmitData(serialprintdebugger);
	#endif
	
	switch (i) {
		case 0:
			return 5;
		break;
		case 1:
			return 10;
		break;
		case 2:
			return 15;
		break;
		case 3:
			return 30;
		break;
		case 4:
			return 60;
		break;
		case 5:
			return 90;
		break;
		case 6:
			return 120;
		break;
		case 7:	
			return 180;
		break;
		case 8:
			return 240;
		break;
		case 9:
			return 300;
		break;
		case 10:
			return 360;
		break;
		case 11:
			return 480;
		default:
			return 0;
		break;
	}// end switch

}
