/*
 * interrupcionesPCINT2.cpp
 *
 * Created: 07/05/2018 20:25:35
 *  Author: Fran
 */ 
#include "interruptionsPCINT2.h"
#include <avr/io.h>
#include <avr/interrupt.h>
#include "VariablesGlobales.h"



volatile uint8_t portdhistory = 0x00;     // OXFF is the pull-up internal is active
uint8_t minus_temp=0, add_temp=0;

void PCINT2_enable (void)
{
	PCICR |= (1 << PCIE2);    // Enable pin change interrupt 2
	PCMSK2 |= (1 << PCINT22) | (1 << PCINT23) ;  // set PCINT23 | PCINT22 to trigger an interrupt on state change
}

void PCINT2_disable (void)
{
	PCICR |= (0 << PCIE2);    // disable pin change interrupt 2
}

ISR (PCINT2_vect)
{
	time_out_menu_inactivity = 0;
	new_pin_change=1;
	uint8_t changedbits;
	changedbits = PIND ^ portdhistory;
	portdhistory = PIND;


	if ((changedbits & (1 << PIND6)))//First change minus
	{
		minus_temp++;
		if (minus_temp==2) {
			minus=1;
			minus_temp=0;
		}
		
	}

	else if((changedbits & (1 << PIND7))) // First change plus
	{
		add_temp++;
		if (add_temp==2) {
			plus=1;
			add_temp=0;
		}

	}
	
	if (!second_click_on_INT0 )
	{
		if (plus>0)
		{
			plus=0;
			menu_cursor_position++;
			if (menu_cursor_position>=(position_cursor_GOOUT+1)) {	menu_cursor_position=0;}// Return position to 0
		}
		else if	(minus>0)
		{
			minus=0;
			if (menu_cursor_position==0) {	menu_cursor_position=(position_cursor_GOOUT+1);}// Return position to 0
			menu_cursor_position--;
		}
	}
}