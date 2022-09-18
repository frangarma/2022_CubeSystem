/* 
* CdadoZone.cpp
*
* Created: 28/07/2022
* Author: Fran
*/


#include "CdadoZone.h"
#include <stdio.h>
#include "definiciones.h"
#include "Cbsp.h"
#include "VariablesGlobales.h"


CdadoZone ::CdadoZone () :Cadc () {}

CdadoZone::CdadoZone (const uint8_t _channel) : Cadc (_channel)
{
} //CdadoZone

CdadoZone::~CdadoZone()
{
} //~CdadoZone

uint8_t CdadoZone :: valor () 
{	
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
    else if ((r >= (arrayValoresResistor[6]-toleranceenohmLecturasResistor)) && ( r <= (arrayValoresResistor[6]+toleranceenohmLecturasResistor))) {	i=6; }
    else if ((r >= (arrayValoresResistor[7]-toleranceenohmLecturasResistor)) && ( r <= (arrayValoresResistor[7]+toleranceenohmLecturasResistor))) {	i=7; }
  	else i=100;// Caso para el default
	
	#ifdef DEBUGGER_MODE
		sprintf(serialprintdebugger, "case_m=%d \r", i);
		UsartTransmitData(serialprintdebugger);
	#endif
	
	switch (i) {
		case 0:
			return i+1;
		break;
		case 1:
			return i+1;
		break;
		case 2:
			return i+1;
		break;
		case 3:
			return i+1;
		break;
		case 4:
			return i+1;
		break;
		case 5:
			return i+1;
		break;
		case 6:
			return i+1;
		break;
		case 7:	
			return i+1;
		break;
		default:
			return 0;
		break;
	}// end switch

}
