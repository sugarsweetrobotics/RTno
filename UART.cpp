#include <Arduino.h>
#include <HardwareSerial.h>
#include "UART.h"


UART::UART(int num, unsigned long baudrate)
{
	switch(num) {
#if defined(UBRRH)
	case 1:
	  m_pSerial = &Serial;
	  break;
#endif
#if defined(UBRR0H)
	case 1:
	  m_pSerial = &Serial;
	  break;
#endif
#if defined(UBRR1H)
		case 1:
		m_pSerial = &Serial1;
		break;
#endif
#if defined(UBRR2H)
		case 2:
		m_pSerial = &Serial2;
		break;
#endif
#if defined(UBRR3H)
		case 3:
		m_pSerial = &Serial3;
		break;
#endif
		default:
		return;
		break;
	}
	m_pSerial->begin(baudrate);
}


UART::~UART()
{
	
}

void UART::write(const void* data, int size)
{
	m_pSerial->write((const uint8_t*)data, size);
}


int UART::available()
{
	return m_pSerial->available();
}


int UART::read()
{
	return m_pSerial->read();
}
