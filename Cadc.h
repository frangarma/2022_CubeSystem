/* 
* cubo.h
*
* Created: 06/04/2018 18:34:08
* Author: Fran
*/


#ifndef __CUBO_H__
#define __CUBO_H__

#include <stdint.h>


class Cadc {

	private:
		uint8_t channel;
	public:
		Cadc();
		Cadc(const uint8_t _channel);
		~Cadc();
		void pin_manager(void);
		void init(void);
		uint16_t read(void);	

}; //end Cadc

#endif //__CUBO_H__


	
	