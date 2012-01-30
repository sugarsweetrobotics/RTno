#ifndef UART_HEADER_INCLUDED
#define UART_HEADER_INCLUDED

#include "SerialDevice.h"
#include <HardwareSerial.h>

void UART_init(unsigned char num, unsigned long baudrate);
void UART_putc(const char c);
uint8_t UART_available();
char UART_getc();

#endif
