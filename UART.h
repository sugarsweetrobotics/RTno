#ifndef UART_HEADER_INCLUDED
#define UART_HEADER_INCLUDED

#include "SerialDevice.h"
#include <HardwareSerial.h>

void UART_init(unsigned char num, unsigned long baudrate);

#endif
