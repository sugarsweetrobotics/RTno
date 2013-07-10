#ifndef SERIAL_DEVICE_HEADER_INCLUDED
#define SERIAL_DEVICE_HEADER_INCLUDED

#include <stdint.h>

#define TIMEOUT 1


extern void(*SerialDevice_putc)(const char c);
extern uint8_t(*SerialDevice_available)();
extern uint8_t(*SerialDevice_getc)();

extern int32_t INFINITE;
int8_t SerialDevice_read(uint8_t* buffer, const uint8_t size, const uint32_t &wait_usec=INFINITE);
#endif
