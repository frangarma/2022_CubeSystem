/* 
* Csistema.h
*
* Created: 26/06/2020 18:56:20
* Author: fgm97
*/


#ifndef __CSISTEMA_H__
#define __CSISTEMA_H__

#include "Chw.h"
#include <stdint.h>
#include "CzonaRiego.h"
#include "Cclock.h"
#include "Clcd.h"
#include "definiciones.h"
#include "Ccanvas.h"
#include <util/delay.h>
#include "CeepromAVR.h"





class Csistema
{

	public:
		typedef enum {standBy, progMode, menuMode} systemStatus;

	private:
		Chw hw;
		Cclock clock;
		Cfecha horaActual;	
		Clcd	lcd;	
		Ccanvas canvas;
		uint8_t numZonas;
		CzonaRiego zonaRiego[NUMZONASSISTEMA];
		CzonaRiego zonaRiego_01;// =CzonaRiego(1, 0x01, 'B');// Decimal correspondence to pin is PINB0
		CzonaRiego zonaRiego_02;// =CzonaRiego(2, 0x10, 'D');// Decimal correspondence to pin is PIND4
		systemStatus status, lastStatus;
		Ci2c* i2csystem; 
		CeepromAVR avreeprom;
		CdadoZone dadoZone;
		CdadoDia dadoDia;
  		CdadoHora dadoHora;
  		CdadoDuracion dadoDuracion;


	//functions
	public:

		/** Method Csistema::Csistema(uint8_t) constructor with parameters
		 * Brief: Update horaActual of system, taking it from rtc, i.e. (clock.obtenerFecha(horaActual) -Cclock:: obtenerFecha(Cfecha& fecha) )
		 * @param uint8_t _numZonas, that is a constant defined in definicioneds.h (NUMZONASSISTEMA)
		 * @return void
		 **/
		Csistema(uint8_t _numZonas = 1);
		~Csistema();
		Csistema( const Csistema &c );
		Csistema& operator=( const Csistema &c );
		void inicializa();
		Chw damehw();
		CzonaRiego* getDroppingZone_01();
		CzonaRiego* getDroppingZone_02();	
		void wait_500ms();

		/** Method Csistema::refreshDate
		 * Brief: Update horaActual of system, taking it from rtc, i.e. (clock.obtenerFecha(horaActual) -Cclock:: obtenerFecha(Cfecha& fecha) )
		 * @param void
		 * @return void
		 **/
		void refreshDate(void);
		void refreshCanvas(lcdmodes lcdmode);
		void clearLcd(void);
		void menuScroll(void);
		void modeProgramming(void);
		static void debug(int);
		Cfecha getDate(void);

		/** Method Csistema::setStatus
		 * Brief: Set up both, status and lastStatus
		 * @param void
		 * @return void
		 **/
		void setStatus(systemStatus);
		systemStatus getStatus();
		systemStatus getLastStatus();
		CeepromAVR* getAvrEeprom();
	
	
	protected:
	private:

	

}; //Csistema

#endif //__CSISTEMA_H__
