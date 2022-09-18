/* 
* Cbsp_.cpp
*
* Created: 26/06/2020 19:08:09
* Author: fgm97
*/


#include "Chw.h"
//#include "Cbsp.h"
#include "definiciones.h"
#include "Ci2c.h"
#include <avr/io.h>
#include <util/twi.h>
//#include <avr/interrupt.h>
#include <avr/wdt.h>
#include "VariablesGlobales.h"


// default constructor
Chw::Chw()
{
	adc = Cadc();
	i2c = Ci2c();
	initialConfiguration();
	initiatePerifheral();
} //Chw

// default destructor
Chw::~Chw()
{
} //~Chw



void Chw::initialConfiguration (void)
{
	pin_manager();
	#if defined (DEBUGGER_MODE_R) || defined (DEBUGGER_MODE)
		UsartInit(BAUD_PRESCALE);
	#endif
	INT0_enable();
	INT1_enable();
	PCINT2_enable();
	WDT_Init();
	TIMER1_enable();
}


void Chw::initiatePerifheral (void)
{
	wdt_clear_init();	
	adc.init();
	i2c.init();
}


void Chw::pin_manager()
{
	//Configurations of digital to analog converter pins
	adc.pin_manager();
	pin_manager_digital_gpio();
}


void Chw::pin_manager_digital_gpio(){
	
	//Configuration of digital input pin
		
	//Configuration of digital output pin
	//ToDo: configure port's number in function of const NUMZONASSISTEMA (definiciones.h)
	DDRB |=(1<<PINB0);//Digital output associated to switch of zone 1
	DDRB |=(1<<PINB1);//Digital output associated to Led1=Activity
	DDRB |=(1<<PINB2);//Digital output associated to Led2=Fail
	DDRD |=(1<<PIND2);//Digital output associated to switch of zone 2
	DDRD |=(1<<PIND3);//Digital output associated to switch of zone 3
	DDRD |=(1<<PIND4);//Digital output associated to switch of zone 4
	DDRD |=(1<<PIND5);//Digital output associated to switch of zone 5
	DDRD |=(1<<PIND6);//Digital output associated to switch of zone 6
	DDRD |=(1<<PIND7);//Digital output associated to switch of zone 7
	//ToDo: See if is possible to configure this pin ADC6 as GPIO and has some relation witn TQFP-32 package. Possible option would be to use PB7 pin
	DDRB |=(1<<PINB7);//Digital output associated to switch of zone 8
			
	//CONFIGURATION SDA & SCL PIN of I2C protocol in PORT C: Used pull-up resistor in PCB
	//Note that is not necessary configure de DDRC�s pin corresponding
	PORTC|= (1<<PINC4) | (1<<PINC5); //Pin 4 & 5 PULL UP TO I2C PROTOCOL
		
	// Configure UART's pins
	//PIND0: RX / PIND1 TX; Note that is not necessary configure thee DDRC�s pin corresponding
}





void Chw::TIMER1_enable(void)
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
	 //To prevent the lack of CPU frecuency definition
	 #warning "Not defined macro F_CPU: 8MHZ nor 16 MHZ in definitios"
	#endif

	//Clear ICF1, clear pending interrupts
	TIFR1 = 1<<ICF1;
	
	// enable timer compare interrupt
	TIMSK1 |= (1 << OCIE1A);
	
	
	TCNT1H=0;
	TCNT1L=0;
}

void Chw::TIMER1_enable_Fast(void)
{
	TCCR1A = 0;     // set entire TCCR1A register to 0
	TCCR1B = 0;     // same for TCCR1B
	
	// set compare match register to desired timer count
 	#ifdef F_CPU_8MHZ 
 
 		OCR1A = 31250/2;// --> 0.5 SECOND, having into account FCPU 8 MHz and prescaler 256
 		TCCR1B = (1 << WGM12) | (1 << CS12) | (0 << CS11) | (0 << CS10);
			
 	#elif F_CPU_16MHZ 
 		OCR1A=15625;//  --> 1 SECOND, having into account FCPU 16 MHz and prescaler 1024
 		TCCR1B = (1 << WGM12) | (1 << CS10) | (1 << CS12);
	 
	#else 
	 //To prevent the lack of CPU frecuency definition
	 #warning "Not defined macro F_CPU: 8MHZ nor 16 MHZ in definitios"
	#endif

	//Clear ICF1, clear pending interrupts
	TIFR1 = 1<<ICF1;
	
	// enable timer compare interrupt
	TIMSK1 |= (1 << OCIE1A);
	
	
	TCNT1H=0;
	TCNT1L=0;
}

void Chw::TIMER1_disable(void)
{TCCR1B=0x00;	}
	


//initialize watchdog 

void Chw::WDT_Init(void)
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

//This function aims to avoid eternal loop due to accidetally enable of wdt
void Chw::wdt_clear_init(void){
	MCUSR |= (0<<WDRF);
	WDTCSR |= (1<<WDCE) | (1<<WDE);	
}






void Chw::INT0_enable (void)
{
	EIMSK |=(1<<INT0);
	EICRA |= (1<<ISC00) |(1<<ISC01); //The rasing edge of INT0 generates an interrupt request.
	//sei();//Line in main function
}

void Chw::INT0_disable (void)
{
	EICRA=0;
	EIMSK |=(0<<INT0);
}


void Chw::INT1_enable (void) {
	EIMSK |=(1<<INT1);
	EICRA |= (1<<ISC10) |(1<<ISC11); ;//The raising edge of INT1 generates an interrupt request.
	//sei();//Line in main function
}

void Chw::INT1_disable (void) {
	EICRA=0;
	EIMSK |=(0<<INT1);
}

void Chw::PCINT2_enable (void)
{
	PCICR |= (1 << PCIE2);    // Enable pin change interrupt 2
	PCMSK2 |= (1 << PCINT22) | (1 << PCINT23) ;  // set PCINT23 | PCINT22 to trigger an interrupt on state change
}

void Chw::PCINT2_disable (void)
{
	PCICR |= (0 << PCIE2);    // disable pin change interrupt 2
}


void Chw::UsartInit( unsigned int baud )
{
	/* Set baud rate */
	UBRR0H = (unsigned char)(baud>>8);
	UBRR0L = (unsigned char)baud;
	/* Enable receiver and transmitter, enables interrupt on the RXC1 Flag */
	UCSR0B = (1<<RXEN0)|(1<<TXEN0)|(1<<RXCIE0);
	/* Set frame format: 8data, 1 stop bit */
	UCSR0C = (0<<USBS0)|(1<<UCSZ00)|(1<<UCSZ01);
}
void Chw::UsartTransmitByte( const char byte )
{
	/* Wait for empty transmit buff */
	while ( !( UCSR0A & (1<<UDRE0)) )
	;
	/* Put data into buff, sends the data */
	UDR0 = byte;
}

unsigned char Chw::UsartReceive( void )
{
	/* Wait for data to be received */
	while ( !(UCSR0A & (1<<RXC0)) )
	;
	/* Get and return received data from buff */
	return UDR0;
}

void Chw::UsartTransmitData(const char * s)
{
	while(*s!=0){
		UsartTransmitByte(*s);
	*s++;}
}

Ci2c* Chw::getI2c(void)
{
	return &(this->i2c);
}
