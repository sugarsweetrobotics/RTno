#ifndef SERIAL_DEVICE_HEADER_INCLUDED
#define SERIAL_DEVICE_HEADER_INCLUDED

#include <stdint.h>

extern void(*SerialDevice_setTarget)(const char* address);


extern void(*SerialDevice_write)(const int8_t* src, const uint8_t size);

/**
 * If correctly received data, this will return positive value.
 */
extern int8_t(*SerialDevice_receive)();

/**
 * If data is still in rxBuffer, this will return the size remained.
 */
extern uint8_t(*SerialDevice_available)();

extern char(*SerialDevice_getc)();
extern void(*SerialDevice_putc)(const char c);

extern uint8_t(*SerialDevice_read)(int8_t* dst, const uint8_t size);


#endif
