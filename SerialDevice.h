#ifndef SERIAL_DEVICE_HEADER_INCLUDED
#define SERIAL_DEVICE_HEADER_INCLUDED

#include <stdint.h>

/**
 * If correctly received data, this will return positive value.
 */
extern int8_t(*SerialDevice_receive)(int8_t* sourceInfo);


/**
 *
 */
extern int8_t(*SerialDevice_write)(const int8_t* target, const int8_t* src, const uint8_t size);


/**
 * If data is still in rxBuffer, this will return the size remained.
 */
extern uint8_t(*SerialDevice_available)();


/**
 * 
 */
extern uint8_t(*SerialDevice_read)(int8_t* dst, const uint8_t size);


#endif
