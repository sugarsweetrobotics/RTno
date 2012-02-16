#define RTNO_SUBMODULE_DEFINE

#include <Arduino.h>
#include <HardwareSerial.h>
#include "UART.h"

static HardwareSerial* m_pSerial;

void UART_init(unsigned char num, unsigned long baudrate)
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
	SerialDevice_setTarget = UART_setTarget;
	SerialDevice_read = UART_read;
	SerialDevice_write = UART_write;
	SerialDevice_putc = UART_putc;
	SerialDevice_getc = UART_getc;
	SerialDevice_available = UART_available;
	m_pSerial->begin(baudrate);
}

void UART_setTarget(const char* address) {
  // Do nothing
}

void UART_write(const int8_t* src, const uint8_t size)
{
  m_pSerial->write((const uint8_t*)src, size);
}

uint8_t UART_read(int8_t* dst, const uint8_t size) {
  for(int i = 0;i < size;i++) {
    dst[i] = UART_getc();
  }
  return size;
}

void UART_putc(const char c) {
  m_pSerial->write((const uint8_t*)&c, 1);
}

uint8_t UART_available()
{
  return m_pSerial->available();
}


char UART_getc()
{
  return m_pSerial->read();
}
