/*
 * definiciones.h
 *
 * Created: 17/03/2018 19:44:01
 *  Author: Fran
 */ 



#ifndef DEFINICIONES_H_
#define DEFINICIONES_H_

#include <stdint.h>
#include <avr/pgmspace.h>

#define F_CPU 8000000UL
#define F_CPU_8MHZ 1

/****** Comment next line to enter y mode debugger through usart messages *****/
//#define	DEBUGGER_MODE_R		1
//#define	DEBUGGER_MODE		1

#define USART_BAUDRATE 9600
#define BAUD_PRESCALE (((F_CPU / (USART_BAUDRATE * 16UL))) - 1)


const PROGMEM uint8_t TimeOutMenuInactivity   = 5;

//It is used typedef in order to work with alias and to simplify the use of tipes lastly

typedef enum {time, temp, HR, temp_prog, title_prog,NR_prog,HR_prog,time_prog, GO_OUT, DoW, clear_prog, prog, titleRiego, lightCicle,lightCicle_1, lightCicleHi, lightCicleMi, lightCicleHf, lightCicleMf, sethoraRiego, setminutoRiego, setminutosRegando, titleReloj, Linea_string_dow, matrizdow, matrizdow_1, matrizdow_2, matrizdow_3, matrizdow_4, matrizdow_5, matrizdow_6, matrizdow_7,sethour, setminutes, setseconds, setday, setmonth, setyear,sethoralightinicio, setminutolightinicio, sethoralightfin, setminutolightfin, riegoActivo } show_info;
typedef enum {standby, prog_mode} states;// extern 
typedef enum {lcdStandby, lcdWorking, lcdProgmode, lcdSubpantallaAjusteRiego, lcdSubpantallaAjusteReloj, greetingScreen} lcdmodes;//extern

#define position_cursor_sethour						0
#define position_cursor_setminutes					1
#define position_cursor_setseconds					2
#define position_cursor_setday						3
#define position_cursor_setmonth					4
#define position_cursor_setyear						5
#define position_cursor_GOOUT						6

// Definitions about of the value of resistance read from cube face
#define Vcc 5
#define toleranceenohmLecturasResistor 190

//#define nElementaarraValoresResistor 7
const uint8_t nelementdoWRiego = 14;
const uint16_t referenceResistor = 10000;
const uint16_t shortcutResistor = 25;
const uint16_t infiniteResistor = 50000;
const uint16_t arrayValoresResistor [] PROGMEM ={1000, 2000, 3000, 4020, 5100, 6040, 6980, 7870, 8870, 9760, 11000, 12100, 13000, 14000, 15000, 16200, 17400, 18200, 19100, 20000 };// Here is defined the possible values of the resistors install in the physicall cube

//Current version lets until 8 zones, using internal GPIO of ATMEGA328P
const uint8_t NUMZONASSISTEMA = 8;

// Definitions in the case of working with several droppings zone

#define offset_factor_0	0
#define offset_factor_1	1
#define num_zonas 4

// Definitions about message

#define TAMANYO_MENSAJE 20


#endif /* DEFINICIONES_H_ */