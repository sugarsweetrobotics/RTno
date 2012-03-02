#define RTNO_SUBMODULE_DEFINE

#include <Arduino.h>
#include <HardwareSerial.h>
#include "UART.h"

static HardwareSerial* m_pSerial;

//void UART_setTarget(const char* address);
//void UART_putc(const char c);
int8_t UART_receive(int8_t* sourceInfo);
uint8_t UART_available();
//char UART_getc();
uint8_t UART_read(int8_t* dst, const uint8_t size);
int8_t UART_write(const int8_t* target, const int8_t* src, const uint8_t size);

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
  //  SerialDevice_setTarget = UART_setTarget;
  SerialDevice_write = UART_write;
  SerialDevice_receive = UART_receive;
  SerialDevice_available = UART_available;
  SerialDevice_read = UART_read;

  m_pSerial->begin(baudrate);
}

int8_t UART_write(const int8_t* target, const int8_t* src, const uint8_t size) {
  if(strncmp((const char*)target, "UART", 4) != 0) return -1;
  m_pSerial->write((const uint8_t*)src, size);
  return size;
}


int8_t UART_receive(int8_t* sourceInfo) {
  memcpy(sourceInfo, "UART", 4);
  return UART_available();
}

uint8_t UART_read(int8_t* dst, const uint8_t size) {
  while(UART_available() <= 0);

  for(int i = 0;i < size;i++) {
    dst[i] = m_pSerial->read();
  }
  return size;
}

uint8_t UART_available()
{
  return m_pSerial->available();
}

