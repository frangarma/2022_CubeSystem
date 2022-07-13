/* 
* CBSP_H
*
* Created: 26/06/2020 19:08:10
* Author: fgm97
*/


#ifndef __CHW__H__
#define __CHW__H__

#include <stdint.h>
#include <avr/interrupt.h>


#include "Cadc.h"
#include "Ci2c.h"
#include "Clcd.h"

class Chw
{
	//variables

	private:
	
		Cadc adc;
		Ci2c i2c;

	//functions
	public:
		Chw();
		~Chw();	

	
		

		void UsartInit( unsigned int baud );
		void UsartTransmitByte( const char byte );
		void UsartTransmitData(const char * s);
		unsigned char UsartReceive(void);
		
		//void adc_init(void);
		//uint16_t read_adc(uint8_t channel);
		void TIMER1_enable(void);
		void TIMER1_enable_Fast(void);
		void TIMER1_disable(void);
		void WDT_Init(void);
		void wdt_clear_init(void);
		void INT0_enable (void);
		void INT0_disable (void);
		void INT1_enable (void);
		void INT1_disable (void);
		void PCINT2_enable (void);
		void PCINT2_disable (void);
	
		void initialConfiguration (void);
		void initiatePerifheral (void);
		Ci2c* getI2c(void);
	
		//static ISR(INT0_vect);
		//static ISR (INT1_vect); 
		//static ISR (PCINT2_vect);
		
	private:
		void pin_manager(void);
		void pin_manager_digital_gpio(void);
	
	protected:

}; //Chw

#endif //__CHW__H__
