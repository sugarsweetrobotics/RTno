#define RTNO_SUBMODULE_DEFINE

#include <Arduino.h>

#include "Transport.h"
#include "Packet.h"

int Transport_init()
{

}


int Transport_SendPacket(const char interface, const char data_length, const char* packet_data) {
  unsigned char sum = 0;
  unsigned char sender[4] = {'U', 'A', 'R', 'T'};
  SerialDevice_putc(interface);
  sum += interface;
  SerialDevice_putc(data_length);
  sum += data_length;

  for(int i = 0;i < 4;i++) {
    sum += sender[i];
    SerialDevice_putc(sender[i]);
  }

  for(int i = 0;i < data_length;i++) {
    sum += packet_data[i];
    SerialDevice_putc(packet_data[i]);
  }
  SerialDevice_putc(sum);
  return PACKET_HEADER_SIZE + data_length + 1;
}

int Transport_ReceivePacket(unsigned char* packet) {
  int counter = 0;
  unsigned char sum = 0;

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
  for(int i = 0;i < 4;i++) {
    unsigned char val = SerialDevice_getc();
    sum += val;
  }

  for(int i = 0;i < packet[DATA_LENGTH];i++) {
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
  unsigned char checksum = SerialDevice_getc();
  
  if(sum != checksum) {
    return -CHECKSUM_ERROR;
  }
  return PACKET_HEADER_SIZE + packet[DATA_LENGTH] + 1;
}
