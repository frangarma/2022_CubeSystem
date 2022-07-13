/*
 * user.c
 *
 * Created: 23/08/2015 0:07:28
 *  Author: Fran
 */ 

#include "Ccanvas.h"
#include "Cbsp.h"
#include "definiciones.h"
#include "variablesglobales.h"
#include <string.h>
#include <stdio.h>



char mensaje[20];
 
uint8_t actual_HR;
unsigned char set_parameter[5];//NR,Tp,HR,Set_time,GoOut_menu



unsigned char new_seg=0;
char dowCalculated[]="DLMXJVS"; // uint8_t DayofWeek (), return: 01 - 07, 01 = Sunday
char dow1[]="LMXJVSD";
char dowaux[15]={};		
uint8_t new_entry_subpantalla=1;
uint8_t horaCambiada=0;
uint8_t segundosCambiados= 0;


Ccanvas::Ccanvas()
{

}

Ccanvas::~Ccanvas()
{

}

Ccanvas::Ccanvas(Csistema* _sistema, Clcd* _lcd, const Cclock& _clock, const Cfecha& _horaActual)
{
	sistema = NULL;
	lcd = NULL;
	
	if (_sistema != NULL)
		sistema = _sistema;
	if (_lcd != NULL)
		lcd = _lcd;
	if (&_clock != NULL)
		clock = _clock;
	if (&_horaActual != NULL)
		horaActual = _horaActual;
}


void Ccanvas::scroll_throug_menu(void)
{
	if (new_entry_mode_prog)
	{
		//read_data();//temp_ntc;get_time()
		horaActual = sistema->getDate();
		refresh(lcdProgmode);
		new_entry_mode_prog=0;
		new_INT0=0;
	}
	else
	{
		toogle=!toogle;
		refresh(lcdProgmode);
	}		
	
}

void Ccanvas::refresh(lcdmodes lcdmode)
{
	switch(lcdmode)
	{
		case greetingScreen:
			;
		break;
	
		case lcdStandby:
	
			horaActual = sistema->getDate();
			showLcd(0,10,time);
			showLcd(3,10,DoW);// Show day of week programmed
			showLcd(5,10,prog);// Show hour, minute and duration of watering programming
			showLcd(7,10,riegoActivo);
		break;	

		case lcdProgmode:
	
			if (new_entry_mode_prog)
			{
				horaActual = sistema->getDate();
				lcd->clear();
 				showLcd(2,10,titleReloj);					
 				showLcd(7,90,GO_OUT);						
			}
			else	
			{
				if (menu_cursor_position==position_cursor_sethour)					{showLcd(2,10,sethour);}
				else if (menu_cursor_position==position_cursor_setminutes)			{showLcd(2,34,setminutes);}
				else if (menu_cursor_position==position_cursor_setseconds)			{showLcd(2,58,setseconds);}
				else if (menu_cursor_position==position_cursor_setday)				{showLcd(5,10,setday);}
				else if (menu_cursor_position==position_cursor_setmonth)			{showLcd(5,34,setmonth);}
				else if (menu_cursor_position==position_cursor_setyear)				{showLcd(5,58,setyear);}	
				else if (menu_cursor_position==position_cursor_GOOUT)				{showLcd(7,90,GO_OUT);}
				//lightCicle, lightCicleHi, lightCicleMi, lightCicleHf, lightCicleMf						
			}	
		break;	
	}//end switch(lcdmode)	
	this->lcd->getChipsetLcd()->drawBuffer();//For 1024 With command send_Data(data)	

} // end void lcd_refresh(lcdmodes lcdmode)



void Ccanvas::showLcd(unsigned char page, unsigned char column, show_info message)
{
	
	if (message==time)
	{
		uint8_t d;
		new_seg=!new_seg;
 		d=DayOfWeek(horaActual.getYear(), horaActual.getMonth(), horaActual.getDay());
 		if (new_seg){
			sprintf(mensaje, DATE_MAIN_CANVAS, horaActual.getHour(), horaActual.getMinute(), dowCalculated[d-1], horaActual.getDay(), horaActual.getMonth() ); 
			lcd->getChipsetLcd()->loadString8x14ToBuffer(column,page, mensaje);
		 }
 		else {
			sprintf(mensaje, " ");
 			lcd->getChipsetLcd()->loadString8x14ToBuffer(column+15,page, mensaje);
		}	
	}
	else if (message==temp)
	{		
		//sprintf(mensaje, "T:%.2i C",actual_temp);
		//sprintf(mensaje, "T:%02d C",actual_temp);
		//lcd.getChipsetLcd().loadStringToBuffer(column,page, mensaje);//Charge buff with string		
	}

	else if (message==DoW)
	{			
		infoDiasRiego(sistema->getDroppingZone_01()->getDiasRiego());
		sprintf(mensaje,"%s",dowaux);
		lcd->getChipsetLcd()->loadString8x14ToBuffer(column,page, mensaje);//Charge buff with string			
	}	

	else if (message==prog)
	{
//		sprintf(mensaje, "%02d:%02d-> %02d  minutos", zonaRiego_01.gethoraRiego(), zonaRiego_01.getminutoInicioRiego(), zonaRiego_01.getDuracionRiego());
		if (sistema->getDroppingZone_01()->gethoraRiego()) 		
		{
			sprintf(mensaje, "%02d:%02d", sistema->getDroppingZone_01()->gethoraRiego(), sistema->getDroppingZone_01()->getminutoInicioRiego());
			lcd->getChipsetLcd()->loadString8x14ToBuffer(column,page, mensaje);//Charge buff with string
		}
		else { // Delete the informtation about dropping hour
			sprintf(mensaje, "     ");
			lcd->getChipsetLcd()->loadString8x14ToBuffer(column,page, mensaje);//Charge buff with string
		}
		if (sistema->getDroppingZone_01()->getDuracionRiego()) {
			sprintf(mensaje, "%02d", sistema->getDroppingZone_01()->getDuracionRiego());
			lcd->getChipsetLcd()->loadString8x14ToBuffer(column+55,page, mensaje);
			
			sprintf(mensaje, "minutos");
			lcd->getChipsetLcd()->loadStringToBuffer(column+75,page+1, mensaje);//Charge buff with string
		}
		else {
			sprintf(mensaje, "       ");
			lcd->getChipsetLcd()->loadString8x14ToBuffer(column+55,page, mensaje);//Charge buff with string
		}
				
		
	}
		else if (message==clear_prog)
		{
			sprintf(mensaje, "                   ");
			lcd->getChipsetLcd()->loadString8x14ToBuffer(column,page, mensaje);//Charge buff with string
		}
	
	else if (message==titleReloj)
	{
		sprintf(mensaje,"%02d:%02d:%.2i", horaActual.getHour(),horaActual.getMinute(), horaActual.getSecond ());
		lcd->getChipsetLcd()->loadString8x14ToBuffer(column,page, mensaje);//Charge buff with string
		sprintf(mensaje,"%02d/%02d/%.2i", horaActual.getDay(),horaActual.getMonth(), horaActual.getYear());
		lcd->getChipsetLcd()->loadString8x14ToBuffer(column,page+3, mensaje);//Charge buff with string
	}
	else if (message==sethour)
	{
		if (toogle) {sprintf(mensaje, "  ");}
		else{sprintf(mensaje,"%.2i", horaActual.getHour());}
		lcd->getChipsetLcd()->loadString8x14ToBuffer(column,page, mensaje);//Charge buff with string
	}
	else if (message==setminutes)
	{
		if (toogle) {sprintf(mensaje, "  ");}
		else{sprintf(mensaje,"%.2i", horaActual.getMinute());}
		lcd->getChipsetLcd()->loadString8x14ToBuffer(column,page, mensaje);//Charge buff with string
	}
	else if (message==setseconds)
	{
		if (toogle) {sprintf(mensaje, "  ");}
		else{sprintf(mensaje,"%.2i", horaActual.getSecond());}
		lcd->getChipsetLcd()->loadString8x14ToBuffer(column,page, mensaje);//Charge buff with string
	}
	else if (message==setday)
	{
		if (toogle) {sprintf(mensaje, "  ");}
		else{sprintf(mensaje,"%.2i", horaActual.getDay());}
		lcd->getChipsetLcd()->loadString8x14ToBuffer(column,page, mensaje);//Charge buff with string
	}
	else if (message==setmonth)
	{
		if (toogle) {sprintf(mensaje, "  ");}
		else{sprintf(mensaje,"%.2i", horaActual.getMonth());}
		lcd->getChipsetLcd()->loadString8x14ToBuffer(column,page, mensaje);//Charge buff with string
	}
	else if (message==setyear)
	{
		if (toogle) {sprintf(mensaje, "  ");}
		else{sprintf(mensaje,"%.2i", horaActual.getYear());}
		lcd->getChipsetLcd()->loadString8x14ToBuffer(column,page, mensaje);//Charge buff with string
	}	
	
	else if (message==riegoActivo) 
	{
		if (sistema->getDroppingZone_01()->isNowRunning()) {
			sprintf(mensaje, "Zona 1 regando %02d m", sistema->getDroppingZone_01()->getDuracionRiego());
			lcd->getChipsetLcd()->loadStringToBuffer(column,page, mensaje);//Charge buff with string

		}
		else if (sistema->getDroppingZone_02()->isNowRunning()) 
		{
			sprintf(mensaje, "Zona 2 regando %02d m", sistema->getDroppingZone_01()->getDuracionRiego());			
			lcd->getChipsetLcd()->loadStringToBuffer(column,page, mensaje);//Charge buff with string	
		}
		
		else if (sistema->getDroppingZone_01()->is_justDroppingNowRunning())
		{
			sprintf(mensaje, "Zona 1 regando %02d m", sistema->getDroppingZone_01()->getDuracionDroppingJustNow());	
			lcd->getChipsetLcd()->loadStringToBuffer(column,page, mensaje);//Charge buff with string		
		}
		else if (sistema->getDroppingZone_02()->is_justDroppingNowRunning())
		{
			sprintf(mensaje, "Zona 2 regando %02d m", sistema->getDroppingZone_02()->getDuracionDroppingJustNow());			
			lcd->getChipsetLcd()->loadStringToBuffer(column,page, mensaje);//Charge buff with string

		}
		else
		{
			sprintf(mensaje,"                   ");
			lcd->getChipsetLcd()->loadStringToBuffer(column,page, mensaje);//Charge buff with string

		}
	}
	
	else if (message==GO_OUT)
	{
		if (toogle) {sprintf(mensaje, "     ");}
		else{sprintf(mensaje, "SALIR");}
		lcd->getChipsetLcd()->loadStringToBuffer(column, page, mensaje);
	}
}






void Ccanvas::enter_programming_mode(void)
{
	static uint8_t plusMenuMode = 0;
	static uint8_t minusMenuMode = 0;
	if (sistema->getDroppingZone_01()->getResultUnionResistanceZoneDices() == unionConditionPlusmenuMode)
	{
		if (plusMenuMode == 0)
		{
			plusMenuMode = 1;
			//poner timer rápido
			sistema->damehw().TIMER1_enable_Fast();
		}
		time_out_menu_inactivity = 0;
	}
	else if (sistema->getDroppingZone_01()->getResultUnionResistanceZoneDices() == unionConditionMinusmenuMode)
	{
		if (minusMenuMode == 0)
		{
			minusMenuMode = 1;
			//poner timer rápido
			sistema->damehw().TIMER1_enable_Fast();
		}
		time_out_menu_inactivity = 0;
	}
	else if (sistema->getDroppingZone_01()->getResultUnionResistanceZoneDices() != unionConditionPlusmenuMode && sistema->getDroppingZone_01()->getResultUnionResistanceZoneDices() != unionConditionMinusmenuMode)
	{
		//Set up timer 1 sg
		sistema->damehw().TIMER1_enable();
	}
		
	if (plusMenuMode) 
	{
// 		plusMenuMode/=2;
		plusMenuMode ++;
		if (plusMenuMode == 2)
		{
			if (menu_cursor_position==position_cursor_sethour)
			{
				if (horaActual.getHour()<23) {horaActual.setHourpp();}
				else horaActual.setHour(0);
				horaCambiada=1;
			}
			else if (menu_cursor_position==position_cursor_setminutes)
			{
				if (horaActual.getMinute()<59) {horaActual.setMinutepp();}
				else horaActual.setMinute(0);
				horaCambiada=1;
			}
			else if (menu_cursor_position==position_cursor_setseconds)
			{
				if (horaActual.getSecond()<59) {horaActual.setSecondpp();}
				else horaActual.setSecond(0);
				segundosCambiados=1;
			}
			else if (menu_cursor_position==position_cursor_setday)
			{
				if (horaActual.getDay()<30) {horaActual.setDaypp();}
				else horaActual.setDay(0);
				horaCambiada=1;
			}
			else if (menu_cursor_position==position_cursor_setmonth)
			{
				if (horaActual.getMonth()<11) {horaActual.setMonthpp();}
				else horaActual.setMonth(0);
				horaCambiada=1;
			}
			else if (menu_cursor_position==position_cursor_setyear)
			{
				if (horaActual.getYear()<99) {horaActual.setYearpp();}
				else horaActual.setYear(0);
				horaCambiada=1;
			}	
			
		}
		if (plusMenuMode == 5)
		{
			plusMenuMode = 0;
		}
		/*		
		else if (menu_cursor_position==position_cursor_GOOUT) { set_go_out_menu +=plus ;}
		plus=0;*/
	}	
	 
	else if (minusMenuMode)
	{
		minusMenuMode++;
		if (minusMenuMode == 2)
			{
// 			minus/=2;
			if (menu_cursor_position==position_cursor_sethour)
			{
				if (horaActual.getHour()>0) {horaActual.setHourll();}
				else horaActual.setHour(23);
				horaCambiada=1;
			}
			else if (menu_cursor_position==position_cursor_setminutes)
			{
				if (horaActual.getMinute()>0) {horaActual.setMinutell();}
				else horaActual.setMinute(59);
				horaCambiada=1;
			}
			else if (menu_cursor_position==position_cursor_setseconds)
			{
				if (horaActual.getSecond()>0) {horaActual.setSecondll();}
				else horaActual.setSecond(59);
				segundosCambiados=1;
			}
			else if (menu_cursor_position==position_cursor_setday)
			{
				if (horaActual.getDay()>0) {horaActual.setDayll();}
				else horaActual.setDay(31);
				horaCambiada=1;
			}
			else if (menu_cursor_position==position_cursor_setmonth)
			{
				if (horaActual.getMonth()>0) {horaActual.setMonthll();}
				else horaActual.setMonth(12);
				horaCambiada=1;
			}
			else if (menu_cursor_position==position_cursor_setyear)
			{
				if (horaActual.getYear()>0) {horaActual.setYearll();}
				else horaActual.setYear(99);
				horaCambiada=1;
			}	
		}
		if (minusMenuMode == 5)
		{
			minusMenuMode = 0;
		}

		/*		
		else if (menu_cursor_position==position_cursor_GOOUT)
		 { 
			 if (set_go_out_menu>0) {set_go_out_menu -=minus ;}
		}
		minus=0;*/
	}		

	
	if (horaCambiada | segundosCambiados)
	{
		horaCambiada=0;
		uint8_t dow_temp=0;
		dow_temp= DayOfWeek(horaActual.getYear(), horaActual.getMonth(), horaActual.getDay());//Avoid to have to adjust manually 
		if (dow_temp==1) { 
			dow_temp=7; 
		}
		else {
			dow_temp--;
		}
		horaActual.setDoW(dow_temp);//Avoid to have to adjust manually 
		if(segundosCambiados)
		{
			clock.asignarFecha(horaActual, true);
			segundosCambiados = 0;
		}
		else
			clock.asignarFecha(horaActual);	
	}
	
	
}//end enter_programming mode


uint8_t Ccanvas::DayOfWeek(int y, uint8_t m, uint8_t d) {   // y > 1752, 1 <= m <= 12
	static int t[] = {0, 3, 2, 5, 0, 3, 5, 1, 4, 6, 2, 4};
	
	y -= m < 3;
	return ((y + y/4 - y/100 + y/400 + t[m-1] + d) % 7) + 1; // 01 - 07, 01 = Sunday
}

void Ccanvas::infoDiasRiego (uint8_t* _diasRiego)
{

	uint8_t i,j=0;

	for (i=0;i<7;i++)
	{
		if (_diasRiego[i]==1)
		{
			dowaux[j]=dow1[i];
			j++;
			dowaux[j]=' ';
			j++;			
		}		
	}
	while (j<13)
	{
		dowaux[j]=' ';
		j++;		
	}
}



 
void Ccanvas::reset(uint8_t &variable)
{
		variable=0;
}