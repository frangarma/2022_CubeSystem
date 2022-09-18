/*
 * VariablesGlobales.h
 *
 * Created: 17/03/2018 19:47:58
 *  Author: Fran
 */ 


#ifndef VARIABLESGLOBALES_H_
#define VARIABLESGLOBALES_H_

#include "Cfecha.h"
#include "CzonaRiego.h"
#include <stdint.h>
#include "Csistema.h"

extern Csistema sistema;
extern states state;
extern lcdmodes lcdmode;
extern const uint8_t Ascii_1[];
extern const uint8_t Ascii_3[];
extern uint8_t new_entry_mode_prog;
extern uint8_t new_event_timer;
extern uint8_t menu_cursor_position;
extern uint8_t toogle;
extern uint8_t set_go_out_menu;//extern
extern const uint16_t arrayValoresResistor[];
//extern Cfecha horaActual;
// extern CzonaRiego zonaRiego_01;
// extern CzonaRiego zonaRiego_02;
//extern char serialprintdebugger[20];
//extern uint8_t actual_temp;
extern Cswitchable led_activity;
extern Cswitchable led_fail;
extern uint8_t time_out_menu_inactivity;



#endif /* VARIABLESGLOBALES_H_ */