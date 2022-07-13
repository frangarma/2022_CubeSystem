/*
 * 1704_InterfazDados_V0.cpp
 *
 * Created: 06/04/2018 13:56:15
 * Author : Fran
 */ 

#include "definiciones.h"
#include <util/delay.h>
#include <stdio.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/wdt.h>

//#include "Cbsp.h"
#include "Csistema.h"
#include "VariablesGlobales.h"
//#include "Cprogramador.h"
#include <avr/eeprom.h>



/*  all digital inputs are 0 by default*/




//volatile uint8_t portdhistory = 0x00;     // OXFF is the pull-up internal is active

//****** things to do to adapt to new PCB *****//
/*

Pull up resisitor present in PCB, so that it has to be removed the corresponding software configuration
ADC0= used to read the out current of 24VAC
INT0/INT1:The raising edge of INT_X generates an interrupt request
PCINT20/PCINT21: Added
PCINT22+/PCINT23: Trigger an interrupt on state change
PB1=Led1=Activity
PB2=Led2=Fail
PB3=Led3=Out_1
Out_aux=ADC6, there is a problem with this pin because of doesn't has assigned port an therefore only can act as a analog pin
Uso de reloj interno
*/


/*
	Used to activate/deactivate droppingJustNow
*/

//ToDo: Add software version variable, model, etc. and, let show it then of restarting of the system
//ToDo: Add new system status, think what things could see usefull for this new status.
//TODO, add fuses configuration to avoid have to configurate manually
// TODO, add the function Dayliht Saving Time and include it inside menu: https://stackoverflow.com/questions/5590429/calculating-daylight-saving-time-from-only-date
// TODO, trabajar tb con la funci�n OLED_PIXEL, para cargar un canvas m�s est�tico
// TODO, a�adir en el reinicio la parte de comunicaciones que permita a�adir zonas anexas a la zona maestra
// TODO, desactivar todo lo innecesario si no se est� en modo debugger (USART, etc...)
// TODO, crear un modo debugger hardware con alguna condici�n de inicio
// TODO, mejorar  #define DS3231_ADDRESS_WRITE	0XD0 / #define DS3231_ADDRESS_READ		0XD1, para ello usar la direcci�n del dispositivo y dos definiciones para hacer una OR I2C_WRITE 0X00, I2C_READ 0X01
//  estas hacerla en una nueva definicion con OR o dentro de la llamada hacer la OR : addr=address<<1; i2c_start(addr|I2C_WRITE);   // I2C_WRITE =0x00
// TODO, fixs functions that manage time, due to currently it hasn't implemented period of dropping time when it involves an hour change.
// TODO, Study if add a hardware fuse Watchdog always on (WDTON) for fail-safe mode.
// Try to reduce the LCD write's times, i.e., only in minutes' changes, dice's changes position, etc...
// TODO, implement different activity's secuenc in order to see the state of the system , 1/s programmed, 5/S unprogrammed, 0.5/s programming
/***** TODO, Notas micro de chinos****/
	//WDT no funciona
	//


//Interruption routine associated with TIMER1 to manage tick actions
ISR(TIMER1_COMPA_vect)
{
	wdt_reset();// To prevent from stopping if running
	new_event_timer=1;
	//Time out for inactivity inside menu
	if (sistema.getStatus()==Csistema::menuMode && time_out_menu_inactivity<TimeOutMenuInactivity )	{
		time_out_menu_inactivity++;
	}
	else if (sistema.getStatus()==Csistema::menuMode && time_out_menu_inactivity>=TimeOutMenuInactivity) {
		//time_out_menu_inactivity=0;
		time_out_menu_inactivity =0;
		//set_go_out_menu++;
		if (menu_cursor_position == position_cursor_GOOUT)
		{
			//Go out from menuMode, restart variables and systemStatuslast
			sistema.setStatus(sistema.getLastStatus());
			time_out_menu_inactivity = 0;
			menu_cursor_position = position_cursor_sethour;		
			toogle = 1;	
			sistema.clearLcd();
		}		
		else
			
			menu_cursor_position++;
		
	}
}

//Interruption routine associated with internal watchdog.
ISR(WDT_vect)
{
	//Here its possible to make things, i.e. turn on a led to signalize reset wdt
	//Or for example write store in eemprom a count wdt reset variable
 	wdt_reset();
	led_fail.on();
	_delay_ms(1000);
	led_fail.off();	
	WDTCSR = (1<<WDIE);// To stay in interrupt and system reset mode WDIE must be set after each interrupt, better out of ISR wdt
	
}

Csistema sistema= Csistema();

//Set hour to the system year= yy-2000; L=1
void setClock(int y = 0, int m = 0, int d = 0, int dow = 0, int h = 0, int mm = 0, int ss = 0);

/***** 2108_InterfazDados_V_Gallo *****/
/***** 01/08/2021 *****/

int main(void) 
{

	//Poner en hora el sistema
	//setClock(22,4,6,3,18,11,00);
	
	Csistema::systemStatus currentSystemstatus;
	sistema.inicializa();	
	sei();//Set enable interrupt
	CzonaRiego* zonRiego1ReadFromeeprom = NULL;
	CzonaRiego* zonRiego2ReadFromeeprom = NULL;

	zonRiego1ReadFromeeprom = sistema.getAvrEeprom()->readZonaRiego(1);
	zonRiego2ReadFromeeprom = sistema.getAvrEeprom()->readZonaRiego(2);

	if (zonRiego1ReadFromeeprom->getcurrentStateZonaRiego() == CzonaRiego::programmed)
	{
		sistema.setStatus(Csistema::progMode);

		//Implementar constructor u operator = para copiar en zona_01 lo leído de forma elegante
		sistema.getDroppingZone_01()->setStatusZonaRiego(CzonaRiego::programmed);
		//sistema.getDroppingZone_01()->setdiasRiego(zonRiego1ReadFromeeprom->getDiasRiego());
		sistema.getDroppingZone_01()->sethoraRiego(zonRiego1ReadFromeeprom->gethoraRiego());
		sistema.getDroppingZone_01()->setminutosRegando(zonRiego1ReadFromeeprom->getDuracionRiego());

		//Para Gallo, la zona_02 se copia de la zona_01, el offset_factor_1 se encargar de desplazar la programación de esta
		//Implementar constructor u operator = para copiar en zona_02 lo leído en zona_01 o eeprom de forma elegante
		sistema.getDroppingZone_02()->setStatusZonaRiego(CzonaRiego::programmed);
		//sistema.getDroppingZone_02()->setdiasRiego(zonRiego1ReadFromeeprom->getDiasRiego());
		sistema.getDroppingZone_02()->sethoraRiego(zonRiego1ReadFromeeprom->gethoraRiego());
		sistema.getDroppingZone_02()->setminutosRegando(zonRiego1ReadFromeeprom->getDuracionRiego());
		
	}

	else
	{
		sistema.setStatus(Csistema::standBy);
	}

	sistema.getDroppingZone_01()->setoffset_factor(offset_factor_0);
	sistema.getDroppingZone_02()->setoffset_factor(offset_factor_1);
	
	while (1)
	{
		if(new_event_timer)
		{
			new_event_timer=0;
			currentSystemstatus = sistema.getStatus();
			switch(currentSystemstatus)
        	{
        	    case Csistema::standBy:
					sistema.refreshDate();		
					sistema.getDroppingZone_01()->doThings(sistema.getDate());
					sistema.getDroppingZone_02()->doThings(sistema.getDate());	
					sistema.refreshCanvas(lcdStandby);
					led_activity.off();
        	    break;

        	    case Csistema::progMode:
					sistema.refreshDate();		
					sistema.getDroppingZone_01()->doThings(sistema.getDate());
					sistema.getDroppingZone_02()->doThings(sistema.getDate());	
					sistema.refreshCanvas(lcdStandby);
					led_activity.blink(); 
        	    break;
	
        	    case Csistema::menuMode: // Case inside menu mode
					sistema.getDroppingZone_01()->doThings(sistema.getDate());
					sistema.menuScroll();
					if(sistema.getStatus() != Csistema::menuMode)
						sistema.clearLcd();					
					sistema.modeProgramming();				
        	    break;
        	}//end switch(currentSystemstatus)

		}//end if(new_event_timer)
		_delay_us(0);
		
	}//end while 1


	return 0;
} // end main

void setClock(int y, int m, int d, int dow, int h, int mm, int ss)
{
	Cclock clock;
	//Cfecha fecha;
	//fecha.asignarFecha(y, m,d, dow, h, mm, ss);
	//clock.asignarFecha(fecha);
	if (ss) clock.setSecond(ss);
 	if (mm) clock.setMinute(mm);
 	if (h) clock.setHour(h);
 	if (dow) clock.setDoW(dow);
 	if (d) clock.setDate(d);
 	if (m) clock.setMonth(m);
 	if (y) clock.setYear(y);

}

