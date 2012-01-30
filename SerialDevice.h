#ifndef SERIAL_DEVICE_HEADER_INCLUDED
#define SERIAL_DEVICE_HEADER_INCLUDED

#include <stdint.h>

extern void(*SerialDevice_putc)(const char c);
extern uint8_t(*SerialDevice_available)();
extern char(*SerialDevice_getc)();

#endif
