/* 
* Csensorlluvia.h
*
* Created: 20/10/2018 19:31:33
* Author: Fran
*/


#ifndef __CSENSORLLUVIA_H__
#define __CSENSORLLUVIA_H__
#include <stdio.h>

#include "Cadc.h"

class Csensorlluvia : Cadc
{
	//variables
	public:
	protected:
	private:

	//functions
	public:
		Csensorlluvia();
		~Csensorlluvia();
		Csensorlluvia (const uint8_t _channel);
		uint8_t valor();
		


}; //Csensorlluvia

#endif //__CSENSORLLUVIA_H__
