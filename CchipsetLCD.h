/* 
* CchipsetLCD.h
*
* Created: 05/07/2020 12:16:28
* Author: fgm97
*/


#ifndef __CCHIPSETLCD_H__
#define __CCHIPSETLCD_H__

#define SLAVE_OLED_WRITE	0b01111000	// Slave address + write
#define SLAVE_OLED_WRITE_ERRONEO	0b11111000	// Slave address + write

#define data_byte		0X40
#define command_byte	0X00

#define SSD1306_DEFAULT_ADDRESS 0x78
#define SSD1306_SETCONTRAST 0x81
#define SSD1306_DISPLAYALLON_RESUME 0xA4
#define SSD1306_DISPLAYALLON 0xA5
#define SSD1306_NORMALDISPLAY 0xA6
#define SSD1306_INVERTDISPLAY 0xA7
#define SSD1306_DISPLAYOFF 0xAE
#define SSD1306_DISPLAYON 0xAF
#define SSD1306_SETDISPLAYOFFSET 0xD3
#define SSD1306_SETCOMPINS 0xDA
#define SSD1306_SETVCOMDETECT 0xDB
#define SSD1306_SETDISPLAYCLOCKDIV 0xD5
#define SSD1306_SETPRECHARGE 0xD9
#define SSD1306_SETMULTIPLEX 0xA8
#define SSD1306_SETLOWCOLUMN 0x00
#define SSD1306_SETHIGHCOLUMN 0x10
#define SSD1306_SETSTARTLINE 0x40
#define SSD1306_MEMORYMODE 0x20
#define SSD1306_COLUMNADDR 0x21
#define SSD1306_PAGEADDR 0x22
#define SSD1306_COMSCANINC 0xC0
#define SSD1306_COMSCANDEC 0xC8
#define SSD1306_SEGREMAP 0xA0
#define SSD1306_CHARGEPUMP 0x8D
#define SSD1306_SWITCHCAPVCC 0x2
#define SSD1306_NOP 0xE3

#define SSD1306_WIDTH 128
#define SSD1306_HEIGHT 64
#define SSD1306_BUFFERSIZE (SSD1306_WIDTH*SSD1306_HEIGHT)/8

#include <stdint.h>
#include "Ci2c.h"


class CchipsetLCD
{
	//variables
	public:
	protected:
	private:
		Ci2c* i2c;
		uint8_t buffer [1024];

	//functions
	public:
	    CchipsetLCD(); 
		CchipsetLCD(Ci2c*);
		~CchipsetLCD();
		void init(void);
		void pixelBuffer(int16_t x, int16_t y);
		void clearBuffer(void);
		void drawBuffer(void);
		void clearChipsetMemory(void);
		void loadCharToBuffer(unsigned char column, unsigned char page, unsigned char letter);
		//Due to lack of memory next method is remove
		//void loadChar8x12ToBuffer (unsigned char column, unsigned char page, unsigned char letter);
		//void loadString8x12ToBuffer (uint8_t column, uint8_t page, char *string);
		void loadChar8x14ToBuffer (unsigned char column, unsigned char page, unsigned char letter);
		void loadString8x14ToBuffer (uint8_t column, uint8_t page, char *string);
		void loadStringToBuffer(uint8_t column, uint8_t page, char *string);
		void line_string_Buffer(uint8_t column, uint8_t page, char *string);
		void draw_pixel(uint8_t x,uint8_t y);
		void sendCommand(uint8_t command);
		void sendCommand_Plus2B(uint8_t command, uint8_t byte_1, uint8_t byte_2);
		void sendData(uint8_t data);
		void seti2cPort(Ci2c*);
		
	protected:
	private:
		

}; //CchipsetLCD

#endif //__CCHIPSETLCD_H__
