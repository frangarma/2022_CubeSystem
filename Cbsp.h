/*
 * BSP.h
 *
 * Created: 03/03/2018 10:50:30
 *  Author: Fran
 */ 


#ifndef __CBSP_H__
#define __CBSP_H__

#include <stdint.h>

void UsartInit( unsigned int baud );
void UsartTransmitByte( const char byte );
void UsartTransmitData(const char * s);
unsigned char UsartReceive(void);
void pin_manager(void);
//void adc_init(void);
//uint16_t read_adc(uint8_t channel);



void TIMER1_enable(void);
void TIMER1_disable(void);

void WDT_Init(void);
void wdt_clear_init(void);

#endif /* __CBSP_H__ */