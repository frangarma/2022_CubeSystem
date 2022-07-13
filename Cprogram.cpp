/*
 * Cprogram.cpp
 *
 * Created: 13/08/2018 16:25:46
 *  Author: Fran
 */ 
#include "Cprogram.h"
#include "Cfecha.h"


//default constructor
Cprogram:: Cprogram() : Cfecha() 
{ 
	programmed = 0;
	running = 0;
	deleted = 0;
	newProgram = false;
	//asignarFecha.init_program();
	//asignarFecha.end_program();	
}

//default destructor


bool Cprogram:: is_programmed() {
	return programmed;
}

void Cprogram::set_program(bool _programmed) {
	programmed=_programmed;
}

bool Cprogram:: is_running() {
	return running;
}

void Cprogram:: set_running(bool _running) {
	running =_running;
}

bool Cprogram:: is_deleted() {
	return deleted;
}

void Cprogram:: set_deleted(bool _deleted) {
	deleted=_deleted;
}

Cfecha Cprogram:: getinitprogram() {

}

void Cprogram:: setinitprogram(Cfecha) {

}

Cfecha Cprogram:: getendprogram() {

}

void Cprogram:: setendprogram(Cfecha) {
	
}

bool Cprogram::is_programRunningNow (Cfecha fecha_Actual) {
	
	//if ( compareDates(fecha_Actual, init_program) ) 
	
	//	return 0;
}