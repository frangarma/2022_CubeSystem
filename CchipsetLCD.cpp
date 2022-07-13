/* 
* CchipsetLCD.cpp
*
* Created: 05/07/2020 12:16:27
* Author: fgm97
*/


#include "CchipsetLCD.h"
#include <string.h>
#include "TimesNewRomans-97-5.h"
#include "TimesNewRomas_8x12.h"
#include "definiciones.h"


// default constructor
CchipsetLCD::CchipsetLCD() 
{
	
}

CchipsetLCD::CchipsetLCD(Ci2c* _i2c) 
{
	if (_i2c != NULL)
	{
		i2c = _i2c;
	}
	memset(buffer, 0, 1024);// void *memset(void *str, int c, size_t n) copies the character c o the first n characters of the string pointed to, by the argument str
} //CchipsetLCD

// default destructor
CchipsetLCD::~CchipsetLCD() {
} //~CchipsetLCD

// Init sequence for 128x64 OLED module
void CchipsetLCD::init(void) {
	// Turn display off
	sendCommand(SSD1306_DISPLAYOFF);//0XAE	
	
	sendCommand(SSD1306_SETMULTIPLEX);//0XA8
	sendCommand(0X3F);
	
	sendCommand(SSD1306_SETDISPLAYOFFSET);//0XD3
	sendCommand(0x00);					// no offset
	
	//sendCommand_1((SSD1306_SETSTARTLINE | 0x00));//0X40, range from 0x40 to 7F
	sendCommand(SSD1306_SETSTARTLINE);	//0X40
	//sendCommand(0x00);					//LINE 0
	
	//sendCommand(SSD1306_SEGREMAP);	//0XA0, two options: 0XA0 | 0XA1
	sendCommand(0XA1);	//0XA1 ESTA ES UNA SEGUNDA OPCION PARA SEGREMAP
	
	sendCommand(SSD1306_COMSCANDEC);//0XC8, two options: 0XC0 | 0XC8, ALLOWING LAYOUT FLEXIBILITY IN THE OLED MODULE
	//sendCommand(0XC0);
	
	sendCommand(SSD1306_SETCOMPINS);	//0XDA
	sendCommand(0x12);					//
	
	sendCommand(SSD1306_SETCONTRAST);//0X81
	sendCommand(0xCF);
	
	sendCommand(SSD1306_DISPLAYALLON_RESUME);	//0XA4
	
	sendCommand(SSD1306_NORMALDISPLAY);	//0XA6 IF INVERTER CHARGE 0XA7
	//sendCommand(0XA7);
	
	sendCommand(SSD1306_SETDISPLAYCLOCKDIV);//0XD5
	sendCommand(0x80);						// the suggested ratio 0x80

	sendCommand(SSD1306_CHARGEPUMP);	//0X8D	Charge pump Setting
	sendCommand(0x14);					// Enable charge pump
	
	sendCommand(SSD1306_MEMORYMODE);	//0X20
	sendCommand(0x00);					//Horizontal address mode	
	
	sendCommand(SSD1306_SETPRECHARGE);//0XD9
	sendCommand(0xF1);	

	sendCommand(SSD1306_SETVCOMDETECT);
	sendCommand(0x40);
	
	sendCommand(SSD1306_DISPLAYON);	//0XAF	
}



void CchipsetLCD::pixelBuffer(int16_t x, int16_t y) {

}

void CchipsetLCD::clearBuffer(void)
{
	memset(buffer, 0, 1024);// void *memset(void *str, int c, size_t n) copies the character c o the first n characters of the string pointed to, by the argument str
}

void CchipsetLCD::drawBuffer(void) 
{
	sendCommand_Plus2B(SSD1306_COLUMNADDR, 0, 127);//0X21, range from 0-127
	sendCommand_Plus2B(SSD1306_PAGEADDR, 0, 7);//0X22, range from 0-7	
	for (uint16_t i=0; i<1024; i++)
	{
		sendData(buffer[i]);
	}
}

void CchipsetLCD::clearChipsetMemory(void)
{
	clearBuffer();
	sendCommand(SSD1306_NORMALDISPLAY);
	this->drawBuffer();
}

void CchipsetLCD::loadCharToBuffer(unsigned char column, unsigned char page, unsigned char letter) 
{
	uint8_t ascii_offset =32;
	for(uint8_t i=0; i<5; i++)
	{
		buffer[i+((page*128)+column)] =pgm_read_byte (&( Ascii_1[(letter-ascii_offset)*5+i]));// In the case of using a simple array -> mono_array[]
	}
}

void CchipsetLCD::loadStringToBuffer(uint8_t column, uint8_t page, char *string) 
{
	uint8_t i = 0;
	while(string[i] != 0 && i< TAMANYO_MENSAJE-1 )
	{
		loadCharToBuffer(column+(5*i), page, string[i]);
		i++;
	}
}

/*void CchipsetLCD::loadChar8x12ToBuffer(unsigned char column, unsigned char page, unsigned char letter) 
{
	uint8_t ascii_offset =32;
	for (uint8_t k=0; k<12;k++) { // Each char takes 12 bytes of memory		
		
		buffer[((page*128)+column)] =pgm_read_byte (&( Ascii_2[(letter-ascii_offset)*12+k]));
		k++;
		buffer[(((page+1)*128)+column)] =pgm_read_byte (&( Ascii_2[(letter-ascii_offset)*12+k]));
		column++;
	}
	
}*/

/*void CchipsetLCD::loadString8x12ToBuffer(uint8_t column, uint8_t page, char *string) 
{
	uint8_t i = 0;
	while(string[i] != 0)
	{
		loadChar8x12ToBuffer(column+(12*i), page, (string[i]));
		i++;
	}
}*/

void CchipsetLCD::loadChar8x14ToBuffer(unsigned char column, unsigned char page, unsigned char letter) 
{
	uint8_t ascii_offset =47;
	for (uint8_t k=0; k<16;k++) { // Each char takes 16 bytes of memory
		if (letter==' ') {
			buffer[((page*128)+column)] =0x00;
			k++;
			buffer[(((page+1)*128)+column)] =0x00;
			column++;
		}
		else {
			buffer[((page*128)+column)] =pgm_read_byte (&( Ascii_3[(letter-ascii_offset)*16+k]));
			k++;
			buffer[(((page+1)*128)+column)] =pgm_read_byte (&( Ascii_3[(letter-ascii_offset)*16+k]));
			column++;
		}
	}

}

void CchipsetLCD::loadString8x14ToBuffer(uint8_t column, uint8_t page, char *string) 
{
	uint8_t i = 0;
	while(string[i] != 0)
	{
		loadChar8x14ToBuffer(column+(8*i), page, (string[i]));
		i++;
	}
}


void CchipsetLCD::draw_pixel(uint8_t x,uint8_t y) {

}

void CchipsetLCD::sendCommand(uint8_t command) {
		i2c->start(SSD1306_DEFAULT_ADDRESS);
		i2c->write(command_byte);
		i2c->write(command);
		i2c->stop();
}

void CchipsetLCD::sendCommand_Plus2B(uint8_t command, uint8_t byte_1, uint8_t byte_2) {
	i2c->start(SSD1306_DEFAULT_ADDRESS);
	i2c->write(command_byte);
	i2c->write(command);
	i2c->write(byte_1);
	i2c->write(byte_2);
	i2c->stop();
}

void CchipsetLCD::sendData(uint8_t data) {
	i2c->start(SSD1306_DEFAULT_ADDRESS);
	i2c->write(data_byte);
	i2c->write(data);
	i2c->stop();
}


void CchipsetLCD::seti2cPort(Ci2c* i2c)
{
	this->i2c = i2c;
}
