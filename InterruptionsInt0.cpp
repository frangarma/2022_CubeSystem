/*
 * InterruptionsInt0.cpp
 *
 * Created: 07/05/2018 20:13:48
 *  Author: Fran
 */ 
#include "interruptionsInt0.h"
#include <avr/io.h>
#include <avr/interrupt.h>
#include "VariablesGlobales.h"




void INT0_enable (void)
{
	EIMSK |=(1<<INT0);
	EICRA |= (1<<ISC00) |(1<<ISC01); //The rasing edge of INT0 generates an interrupt request.
	//sei();//Line in main function
}

void INT0_disable (void)
{
	EICRA=0;
	EIMSK |=(0<<INT0);
}

ISR(INT0_vect)
{
	//EIFR |= (1<< INTF0);//Flag interrupt reset
	time_out_menu_inactivity = 0;
	new_INT0=1;
	if (state!=prog_mode)
	{
		state=prog_mode;
		new_entry_mode_prog=1;
	}
	else if (state==prog_mode && second_click_on_INT0) 	{ third_click_on_INT0++;}	//Second click is = new_INT0 then of new_entry_mode_prog
	
}