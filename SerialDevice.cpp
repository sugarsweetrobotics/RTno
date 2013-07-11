#include "Arduino.h"
#include "SerialDevice.h"

// static value declaration.
void(*SerialDevice_putc)(const char c);
uint8_t(*SerialDevice_available)();
uint8_t(*SerialDevice_getc)();

int32_t INFINITE = -1;

int8_t SerialDevice_read(uint8_t* buffer, const uint8_t size, const uint32_t &wait_usec)
{
  uint32_t start_time = micros();
  for(unsigned int i = 0;i < size;i++) {
    while (1) {
      if(SerialDevice_available() > 0) {
        break;
      }
      
      uint32_t us = micros() - start_time;
      if (us >= wait_usec && wait_usec != INFINITE) {
        return -TIMEOUT;
      }
    }

    buffer[i] = SerialDevice_getc();
  }
  return size;
}


