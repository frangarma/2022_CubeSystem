/* 
* Cdadodia.h
*
* Created: 13/04/2018 14:21:15
* Author: Fran
*/


#ifndef __CDADODIA_H__
#define __CDADODIA_H__

#include "Cadc.h"

typedef enum {L=1, M, X, J, V, S, D, UnosyQuinces, today, tomorrow, dayAfterTomorrow, fiveDaysAfter, tenDaysAfter, twuentyDaysAfter} dayOfWeek;

class CdadoDia : public Cadc {
	//variables
	private:
		bool repetitiveProgram;
		uint8_t* dow;

	//functions
	public:

		CdadoDia ();
		CdadoDia(const uint8_t _channel);
		~CdadoDia();

		/**
		* brief: This method aims to get the properties repetitiveProgram and fill the pointer dow, both given from the cube position dice.
		* @param: uint8_t* _dowRiego, is the pointer to be fill with programmed days
		* @return: void
		*/
		uint8_t* valor(uint8_t *_doWRiego);
		void fillArrayDay( uint8_t*, uint8_t = 0, uint8_t = 0, uint8_t = 0, uint8_t = 0, uint8_t = 0, uint8_t = 0, uint8_t =0, uint8_t = 0, uint8_t = 0, uint8_t = 0, uint8_t = 0, uint8_t = 0, uint8_t =0, uint8_t = 0) ;
		

}; //Cdadodia

#endif //__CDADODIA_H__
