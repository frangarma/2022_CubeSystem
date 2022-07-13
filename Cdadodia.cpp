/* 
* Cdadodia.cpp
*
* Created: 13/04/2018 14:21:14
* Author: Fran
*/


#include "Cdadodia.h"
#include <stdio.h>
#include "definiciones.h"
#include "Cbsp.h"
#include "VariablesGlobales.h"
#include <string.h>
#include <stdlib.h>

 
using namespace std;

CdadoDia ::CdadoDia () :Cadc () {
	
}

CdadoDia :: CdadoDia (const uint8_t _channel) : Cadc(_channel) 
{
	repetitiveProgram = false;
	dow = (uint8_t*) malloc(nelementdoWRiego*sizeof(uint8_t));
	memset(dow, 0, sizeof(dow)) ;
} //Cdadodia

// default destructor
CdadoDia::~CdadoDia() {
	
} //~Cdadodia



uint8_t* CdadoDia::valor(uint8_t *_doWRiego) 
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
	else i=10;// Caso para el default
		
	#ifdef DEBUGGER_MODE
	sprintf(serialprintdebugger, "case_d=%d,", i);
	UsartTransmitData(serialprintdebugger);
	#endif
	
	switch (i) 
	{
		case 0:
			fillArrayDay(_doWRiego, L);
			//_doWRiego[0]=1;_doWRiego[1]=0;_doWRiego[2]=0;_doWRiego[3]=0;_doWRiego[4]=0;_doWRiego[5]=0;_doWRiego[6]=0;_doWRiego[7]=0;//Lunes
			break;
		case 1:
			fillArrayDay(_doWRiego, L, X);
			//_doWRiego[0]=1;_doWRiego[1]=0;_doWRiego[2]=1;_doWRiego[3]=0;_doWRiego[4]=0;_doWRiego[5]=0;_doWRiego[6]=0;_doWRiego[7]=0;//L & X
			break;
		case 2:
			fillArrayDay(_doWRiego, L, X, V);
			//_doWRiego[0]=1;_doWRiego[1]=0;_doWRiego[2]=1;_doWRiego[3]=0;_doWRiego[4]=1;_doWRiego[5]=0;_doWRiego[6]=0;_doWRiego[7]=0;//L & X & V
			break;
		case 3:
			fillArrayDay(_doWRiego, L, X, V, D);
			//_doWRiego[0]=1;_doWRiego[1]=0;_doWRiego[2]=1;_doWRiego[3]=0;_doWRiego[4]=1;_doWRiego[5]=0;_doWRiego[6]=1;_doWRiego[7]=0;//L & X & V & D
			break;
		case 4:
			fillArrayDay(_doWRiego, L, M, X, J, V, S, D);
			//_doWRiego[0]=1;_doWRiego[1]=1;_doWRiego[2]=1;_doWRiego[3]=1;_doWRiego[4]=1;_doWRiego[5]=1;_doWRiego[6]=1;_doWRiego[7]=0;//L&M&X&J&V&S&D
			break;
		case 5:
			fillArrayDay(_doWRiego, UnosyQuinces);
			//_doWRiego[0]=0;_doWRiego[1]=0;_doWRiego[2]=0;_doWRiego[3]=0;_doWRiego[4]=0;_doWRiego[5]=0;_doWRiego[6]=0;_doWRiego[7]=1;// 1 y 15 de cada mes
			break;
		case 6:
			fillArrayDay(_doWRiego, today);
			break;
		case 7:
			fillArrayDay(_doWRiego, tomorrow);
			break;
		case 8:
			fillArrayDay(_doWRiego, dayAfterTomorrow);
			break;
		case 9:
			fillArrayDay(_doWRiego, fiveDaysAfter);
			break;
		case 10:
			fillArrayDay(_doWRiego, tenDaysAfter);
			break;
		case 11:
			fillArrayDay(_doWRiego, twuentyDaysAfter);
			break;		
		default:
			fillArrayDay(_doWRiego);
			//_doWRiego[0]=0;_doWRiego[1]=0;_doWRiego[2]=0;_doWRiego[3]=0;_doWRiego[4]=0;_doWRiego[5]=0;_doWRiego[6]=0;_doWRiego[7]=0;// Caso resistor valor fuera de rang0 --> No programado.
		break;
	}// end switch {	
	
	if (i <6) // case 0 to 5 indicates repepetive program
		repetitiveProgram = true;
	else if (i<12)
		repetitiveProgram = true;

	dow = _doWRiego;

	return dow;		
}

void CdadoDia::fillArrayDay(uint8_t* dow, uint8_t day_1, uint8_t day_2, uint8_t day_3, uint8_t day_4, uint8_t day_5, uint8_t day_6, uint8_t day_7, uint8_t unosyquinces, 
							uint8_t hoy, uint8_t maniana, uint8_t pasadomaniana, uint8_t cincodias, uint8_t diez, uint8_t veintedias)
{
	//Reset all elements
	for(int i=0; i<nelementdoWRiego; i++)
		dow[i] = 0;

	if(day_1 != 0)
		dow[day_1-1] = 1;
	if(day_2 != 0)
		dow[day_2-1] = 1;
	if(day_3 != 0)
		dow[day_3-1] = 1;
	if(day_4 != 0)
		dow[day_4-1] = 1;
	if(day_5 != 0)
		dow[day_5-1] = 1;
	if(day_6 != 0)
		dow[day_6-1] = 1;
	if(day_7 != 0)
		dow[day_7-1] = 1;
	if(unosyquinces != 0)
		dow[unosyquinces-1] = 1;
	if(hoy != 0)
		dow[hoy-1] = 1;
	if(maniana != 0)
		dow[maniana-1] = 1;
	if(pasadomaniana != 0)
		dow[pasadomaniana-1] = 1;
	if(cincodias != 0)
		dow[cincodias-1] = 1;
	if(diez != 0)
		dow[diez-1] = 1;
	if(veintedias != 0)
		dow[veintedias-1] = 1;
}
