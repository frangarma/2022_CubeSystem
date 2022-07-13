/*
 * VariablesGlobales.cpp
 *
 * Created: 17/03/2018 19:47:43
 *  Author: Fran
 */ 

 
 #include "VariablesGlobales.h"


states state=standby;// extern
lcdmodes lcdmode;//extern
uint8_t new_INT0=0;
uint8_t new_pin_change=0;
uint8_t menu_cursor_position=0;
uint8_t toogle=0;//extern
uint8_t third_click_on_INT0=0;//extern
uint8_t second_click_on_INT0 =0;//extern
uint8_t set_go_out_menu;//extern
uint8_t plus=0,minus=0;//extern
//uint8_t actual_temp=0;
Cswitchable led_activity = Cswitchable(0x02, 'B');// Decimal correspondence to pin is PINB1
Cswitchable led_fail = Cswitchable(0x4, 'B'); // Decimal correspondence to pin is PINB2
uint8_t new_event_timer=0;
uint8_t new_entry_mode_prog=0;
uint8_t time_out_menu_inactivity=0;
