/* 
* CdadoHora.cpp
*
* Created: 13/04/2018 16:44:47
* Author: Fran
*/


#include "CdadoHora.h"
#include <stdio.h>
#include "definiciones.h"
#include "Cbsp.h"
#include "VariablesGlobales.h"


// default constructor

CdadoHora ::CdadoHora () :Cadc () {}

CdadoHora :: CdadoHora(const uint8_t _channel) : Cadc(_channel)
{
} //CdadoHora

// default destructor
CdadoHora :: ~CdadoHora()
{
} //~CdadoHora

//This function return a value corresponding to the programming hour in case of 0 it means that the cube is not positioned.
uint8_t CdadoHora :: valor() {
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
		sprintf(serialprintdebugger, "case_h=%d,", i);
		UsartTransmitData(serialprintdebugger);
	#endif
	
 	switch (i) {
		case 0:
			return 7;
		break;		
		case 1:
			return 8;
		break;
		case 2:
			return 9;
		break;
		case 3:
			return 20;
		break;
		case 4:
			return 21;
		break;
		case 5:
			return 22;
		break;
		default:
			return 0;
		break;	
	}// end switch

 }