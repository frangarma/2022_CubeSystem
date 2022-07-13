/* 
* cubo.cpp
*
* Created: 06/04/2018 18:34:08
* Author: Fran
*/


#include "Cadc.h"
#include "Cbsp.h"
#include <avr/io.h>


// default constructor
Cadc::Cadc() {}

Cadc:: Cadc(const uint8_t _channel) {
		channel=_channel;		
}

// default destructor
Cadc::~Cadc()
{
} //~cubo


void Cadc::pin_manager(void)
{
	//Configurations of digital to analog converter pins
	PORTC |= (0<<PINC0)|(0<<PINC1)|(0<<PINC2)|(0<<PINC3);// PINC0 & PINC1 & PINC2 & PINC3: digital to analog conversion ADCO & ADC1 respectively
}

void Cadc::init(void)
{
	ADCSRA |= ((1<<ADPS2)|(1<<ADPS1)|(1<<ADPS0));    //16Mhz/128 = 125Khz the ADC reference clock
	ADMUX  |= (1<<REFS0);                //Voltage reference from Avcc (5v)
	ADCSRA |= (1<<ADEN);                //Turn on ADC
	ADCSRA |= (1<<ADSC);                //Do an initial conversion because this one is the slowest and to ensure that everything is up and running
}

uint16_t Cadc::read(){
	ADMUX &= 0xF0;                    //Clear the older channel that was read
	ADMUX |= channel;                //Defines the new ADC channel to be read from 0 to 7
	ADCSRA |= (1<<ADSC);                //Starts a new conversion
	while(ADCSRA & (1<<ADSC));            //Wait until the conversion is done
	return ADCW;                    //Returns the ADC value of the chosen channel
}