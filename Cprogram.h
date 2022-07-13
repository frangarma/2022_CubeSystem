/*
 * Cprogram.h
 *
 * Created: 13/08/2018 16:26:14
 *  Author: Fran
 */ 


#ifndef CPROGRAMA_H_
#define CPROGRAMA_H_

#include "Cfecha.h"

class Cprogram  : public Cfecha {
	
	private:
		bool newProgram;
		bool programmed;
		bool running;
		bool deleted;
		Cfecha init_program;
		Cfecha end_program;
		
	
	
	
	public:
		Cprogram();
		bool is_programmed();
		void set_program(bool);
		bool is_running();
		void set_running(bool);
		bool is_deleted();
		void set_deleted(bool);
		Cfecha getinitprogram();
		void setinitprogram(Cfecha);
		Cfecha getendprogram();
		void setendprogram(Cfecha);
		bool is_programRunningNow(Cfecha);
		
	
};



#endif /* CPROGRAMA_H_ */