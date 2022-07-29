/* 
* CdadoZone.h
*
* Created: 28/07/20200
* Author: Fran
*/


#ifndef __CDADOZONE_H__
#define __CDADOZONE_H__

#include "Cadc.h"

class CdadoZone :public Cadc
{

	private:

//functions
	public:

        /**
		 * Method: CdadoZone()
		 * Brief: Default constructor
		 * @param: void
		 * @return: void
		 */
	    CdadoZone();

        /**
		 * Method: CdadoZone()
		 * Brief: Constructor wth params
		 * @param: const uint8_t _channel: Fix the ADC channel according to hardware
		 * @return: void
		 */
	    CdadoZone(const uint8_t _channel);

        /**
		 * Method: ~CdadoZone()
		 * Brief: Default destructor
		 * @param: void
		 * @return: void
		 */
	    ~CdadoZone();

        /**
		 * Method: valor()
		 * Brief: Read and determine the zone selected
		 * @param: void
		 * @return: uint8_t values from [0..8]; where 0 indicates not selection and 1 to 8 indicates the zone selected.
		 */
	    uint8_t valor();


}; //CdadoZone

#endif //__CDADOZONE_H__