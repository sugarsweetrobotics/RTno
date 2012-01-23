#ifndef UART_HEADER_INCLUDED
#define UART_HEADER_INCLUDED

#include "SerialDevice.h"
#include <HardwareSerial.h>

void UART_init(unsigned char num, unsigned long baudrate);
void UART_putc(const char c);
unsigned char UART_available();
char UART_getc();

#if 0
class UART : public SerialDevice {
private:
	
protected:
	HardwareSerial* m_pSerial;


public:
	UART(int num, unsigned long baudrate);

	virtual ~UART();

public:
	/**
	 * Write Specific Byte Data.
	 */
	virtual void write(const void* data, int size);
	
	/**
	 * Return Received Buffer Size.
	 */
	virtual int available();
	
	/**
	 * Read One Byte.
	 */
	virtual int read();

};
#endif

#endif
