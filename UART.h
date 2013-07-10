#pragma once

#include "SerialDevice.h"
#include <HardwareSerial.h>

void UART_init(unsigned char num, unsigned long baudrate);
void UART_putc(const char c);
uint8_t UART_available();
uint8_t UART_getc();
