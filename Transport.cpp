#define RTNO_SUBMODULE_DEFINE
#include <stdint.h>
#include <Arduino.h>

#include "Transport.h"
#include "Packet.h"

int8_t Transport_init()
{

}


int8_t Transport_SendPacket(const char interface, const uint8_t data_length, const int8_t* packet_data) {
  uint8_t sum = 0;
  uint8_t sender[4] = {'U', 'A', 'R', 'T'};
  SerialDevice_putc(interface);
  sum += interface;
  SerialDevice_putc(data_length);
  sum += data_length;

  for(uint8_t i = 0;i < 4;i++) {
    sum += sender[i];
    SerialDevice_putc(sender[i]);
  }

  for(uint8_t i = 0;i < data_length;i++) {
    sum += packet_data[i];
    SerialDevice_putc(packet_data[i]);
  }
  SerialDevice_putc(sum);
  return PACKET_HEADER_SIZE + data_length + 1;
}

int8_t Transport_ReceivePacket(int8_t* packet) {
  uint8_t counter = 0;
  uint8_t sum = 0;

  if(SerialDevice_available() == 0) {
    return 0;
  }

  while(SerialDevice_available() < PACKET_HEADER_SIZE) {
    delayMicroseconds(PACKET_WAITING_DELAY);
    counter++;
    if(counter == PACKET_WAITING_COUNT) {
      return -TIMEOUT;
    }
  }
  packet[INTERFACE] = SerialDevice_getc();
  sum += packet[INTERFACE];
  packet[DATA_LENGTH] = SerialDevice_getc();
  sum += packet[DATA_LENGTH];

  counter = 0;
  while(SerialDevice_available() < 4) {
    delayMicroseconds(PACKET_WAITING_DELAY);
    counter++;
    if(counter == PACKET_WAITING_COUNT) {
      return -TIMEOUT;
    }
  }
  for(uint8_t i = 0;i < 4;i++) {
    uint8_t val = SerialDevice_getc();
    sum += val;
  }

  for(uint8_t i = 0;i < packet[DATA_LENGTH];i++) {
    counter = 0;
    while(SerialDevice_available() == 0) {
      delayMicroseconds(PACKET_WAITING_DELAY);
      counter++;
      if(counter == PACKET_WAITING_COUNT) {
	return -DATA_TIMEOUT;
      }
    }
    packet[PACKET_HEADER_SIZE+i] = SerialDevice_getc();
    sum += packet[PACKET_HEADER_SIZE+i];
  }
  
  while(SerialDevice_available() == 0) {
    ;
  }
  uint8_t checksum = SerialDevice_getc();
  
  if(sum != checksum) {
    return -CHECKSUM_ERROR;
  }
  return PACKET_HEADER_SIZE + packet[DATA_LENGTH] + 1;
}
