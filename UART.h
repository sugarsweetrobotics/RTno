#ifndef UART_HEADER_INCLUDED
#define UART_HEADER_INCLUDED

#include "SerialDevice.h"
#include <HardwareSerial.h>

void UART_init(unsigned char num, unsigned long baudrate);
void UART_setTarget(const char* address);
void UART_putc(const char c);
int8_t UART_receive();
uint8_t UART_available();
char UART_getc();
uint8_t UART_read(int8_t* dst, const uint8_t size);
void UART_write(const int8_t* src, const uint8_t size);

#endif
