#ifndef _CI2C_H_
#define _CI2C_H_   


#include <stdint.h>

class Ci2c{
	
	public:
	
		Ci2c();
		~Ci2c();
		void init(void);
		unsigned char start(unsigned char addr);
		void start_wait(unsigned char addr);
		unsigned char rep_start(unsigned char addr);
		unsigned char write(uint8_t data);
		unsigned char readAck(void);
		unsigned char readNak(void);
		void stop(void);
};

#endif //_CI2C_H_
