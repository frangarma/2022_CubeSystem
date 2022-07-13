/*
 * interrupcionesInt1.cpp
 *
 * Created: 07/05/2018 20:31:57
 *  Author: Fran
 */ 
#include "interruptionsInt1.h"
#include <avr/io.h>
#include <avr/interrupt.h>
#include "VariablesGlobales.h"


void INT1_enable (void) {
	EIMSK |=(1<<INT1);
	EICRA |= (1<<ISC10) |(1<<ISC11); ;//The raising edge of INT1 generates an interrupt request.	
	//sei();//Line in main function
}

void INT1_disable (void) {
	EICRA=0;
	EIMSK |=(0<<INT1);
}

ISR (INT1_vect) {
	//TODO, a�adir condici�n para el caso de programa activo y corriendo no permitir entrar el droppinJustNow
	//TODO, a�adir condiciones para el caso de droppingJustNow que haga un recorrido secuencial desde INT1, i.e., 1 click solo recorrido completo por zonas hasta finalizar DJN
	// caso de 2� click mientras DJN en Z1 salte a Z2 y finalice s�lo, caso 3� click mientras DJN en Z2 finalizaci�n completa DJN.
	
	if (sistema.getDroppingZone_01()->is_justDroppingNowRunning()) {
			//zonaRiego_01.setStateJustDroppingNow(0); // Inside the method me_toca_algo_que_hacer(), is changed the running value and off() the switch
			sistema.getDroppingZone_01()->ResetDroppingJustNow();
	}
	else {
		//sistema.getDroppingZone_01()->setStateJustDroppingNow(1);
	}
	
	if (sistema.getDroppingZone_02()->is_justDroppingNowRunning()) {
//		zonaRiego_02.setStateJustDroppingNow(0); // Inside the method me_toca_algo_que_hacer(), is changed the running value and off() the switch
		sistema.getDroppingZone_02()->ResetDroppingJustNow();
	}
	else {
		//sistema.getDroppingZone_02()->setStateJustDroppingNow(1);
	}
	
}