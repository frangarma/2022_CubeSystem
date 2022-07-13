/*
 * BSP.cpp
 *
 * Created: 03/03/2018 10:50:11
 *  Author: Fran
 */ 

#define F_CPU 8000000UL

#include "Cbsp.h"
#include "definiciones.h"
#include "Ci2c.h"
#include <avr/io.h>
#include <util/twi.h>
#include <avr/interrupt.h>
#include <avr/wdt.h>


void UsartInit( unsigned int baud )
{
	/* Set baud rate */
	UBRR0H = (unsigned char)(baud>>8);
	UBRR0L = (unsigned char)baud;
	/* Enable receiver and transmitter, enables interrupt on the RXC1 Flag */
	UCSR0B = (1<<RXEN0)|(1<<TXEN0)|(1<<RXCIE0);
	/* Set frame format: 8data, 1 stop bit */
	UCSR0C = (0<<USBS0)|(1<<UCSZ00)|(1<<UCSZ01);
}
void UsartTransmitByte( const char byte )
{
	/* Wait for empty transmit buff */
	while ( !( UCSR0A & (1<<UDRE0)) )
	;
	/* Put data into buff, sends the data */
	UDR0 = byte;
}

unsigned char UsartReceive( void )
{
	/* Wait for data to be received */
	while ( !(UCSR0A & (1<<RXC0)) )
	;
	/* Get and return received data from buff */
	return UDR0;
}

void UsartTransmitData(const char * s)
{
	while(*s!=0){
		UsartTransmitByte(*s);
	*s++;}
}

void pin_manager(void)
{

	//Configuration of digital input pin	
	
	DDRD |=(0<<PIND2);//Digital input INT0, open menu/enter
	DDRD |=(0<<PIND3);//Digital input INT1, Dropping just now
	DDRD |=(0<<PIND6);//Digital input PCINT22, switch minus
	DDRD |=(0<<PIND7);//Digital input PCINT23, switch plus
	
	DDRD |=(0<<PIND5);//Digital input PCINT21, to detect changes in dice position
	
	//Configuration of digital output pin
	
	DDRB |=(1<<PINB0);//Digital output associated to switch of zone 1
	DDRB |=(1<<PINB1);//Digital output associated to Led1=Activity
	DDRB |=(1<<PINB2);//Digital output associated to Led2=Fail
	//DDRC |= ();//Digital output associated to Out_aux, currently associated with wrong pin ADC6
	DDRD |=(1<<PIND4);//Digital output PCINT20, used as zonaRiego.02
	
	//Configurations of digital to analog converter pins
	PORTC |= (0<<PINC0)|(0<<PINC1)|(0<<PINC2)|(0<<PINC3);// PINC0 & PINC1 & PINC2 & PINC3: digital to analog conversion ADCO & ADC1 respectively
	
	//CONFIGURATION SDA & SCL PIN of I2C protocol in PORT C: Used pull-up resistor in PCB
	//Note that is not necessary configure de DDRC�s pin corresponding	
	//PORTC|= (1<<PINC4) | (1<<PINC5); //Pin 4 & 5 PULL UP TO I2C PROTOCOL
	
	// Configure UART's pins
	//PIND0: RX / PIND1 TX; Note that is not necessary configure thee DDRC�s pin corresponding	

}

// void adc_init(void){
// 	ADCSRA |= ((1<<ADPS2)|(1<<ADPS1)|(1<<ADPS0));    //16Mhz/128 = 125Khz the ADC reference clock
// 	ADMUX  |= (1<<REFS0);                //Voltage reference from Avcc (5v)
// 	ADCSRA |= (1<<ADEN);                //Turn on ADC
// 	ADCSRA |= (1<<ADSC);                //Do an initial conversion because this one is the slowest and to ensure that everything is up and running
// }
// 
// uint16_t read_adc(uint8_t channel){
// 	ADMUX &= 0xF0;                    //Clear the older channel that was read
// 	ADMUX |= channel;                //Defines the new ADC channel to be read from 0 to 7
// 	ADCSRA |= (1<<ADSC);                //Starts a new conversion
// 	while(ADCSRA & (1<<ADSC));            //Wait until the conversion is done
// 	return ADCW;                    //Returns the ADC value of the chosen channel
// }
// 




void TIMER1_enable(void)
{
	TCCR1A = 0;     // set entire TCCR1A register to 0
	TCCR1B = 0;     // same for TCCR1B
	
	// set compare match register to desired timer count
 	#ifdef F_CPU_8MHZ 
 
 		OCR1A = 31250;// --> 1 SECOND, having into account FCPU 8 MHz and prescaler 256
 		TCCR1B = (1 << WGM12) | (1 << CS12) | (0 << CS11) | (0 << CS10);
			
 	#elif F_CPU_16MHZ 
 		OCR1A=15625;//  --> 1 SECOND, having into account FCPU 16 MHz and prescaler 1024
 		TCCR1B = (1 << WGM12) | (1 << CS10) | (1 << CS12);
	 
	 #else 
	 /To prevent the lack of CPU frecuency definition
	 #warning "Not defined macro F_CPU: 8MHZ nor 16 MHZ in definitios"
	 #endif

// 		OCR1A = 31250;// --> 1 SECOND, having into account FCPU 8 MHz and prescaler 256
// 		TCCR1B = (1 << WGM12) | (1 << CS12) | (0 << CS11) | (0 << CS10);
	
	
	// Turn on CTC modeSet CS10 and CS12 bits for 1024 prescaler
	//TCCR1B = (1 << WGM12) | (1 << CS10) | (1 << CS12);
	//Prescaler 256
	//TCCR1B = (1 << WGM12) | (1 << CS12) | (0 << CS11) | (0 << CS10);/
	
	//Clear ICF1, clear pending interrupts
	TIFR1 = 1<<ICF1;
	
	// enable timer compare interrupt
	TIMSK1 |= (1 << OCIE1A);
	
	
	TCNT1H=0;
	TCNT1L=0;
}

void TIMER1_disable(void)
{TCCR1B=0x00;	}
	


//initialize watchdog 

void WDT_Init(void)
{
	/*
	//disable interrupts
	cli();
	//reset watchdog
	wdt_reset();	

	//set up WDT interrupt
	WDTCSR = (1<<WDCE)|(1<<WDE);
	//Start watchdog timer with 4s prescaller
	WDTCSR |= (1<<WDIE) | (1<<WDP3) | (1<<WDE);
	//Enable global interrupts
	//sei();// in main program	
	//WDTON fuse programmed to make a hardware reset 
	*/
	//disable interrupts
	cli();
	//reset watchdog
	wdt_reset();
	MCUSR = 0;
	wdt_disable();
	wdt_enable(WDTO_4S);
	

}


// void WDT_Init(void)
// {
// 	asm volatile("cli");
// 	asm volatile("wdr");               //watchdog reset
// 	MCUSR &= (1<<WDRF);
// 	WDTCSR |= (1<<WDCE) | (1<<WDE);
// 	WDTCSR = 0;
// 	asm volatile("sei");
// }
void wdt_clear_init(void){
	MCUSR |= (0<<WDRF);
	WDTCSR |= (1<<WDCE) | (1<<WDE);	
}
