#define RTNO_SUBMODULE_DEFINE
#include <stdint.h>
#include "Arduino.h"

#include "Transport.h"
#include "Packet.h"

int8_t Transport_init()
{
    return 0;
}


int8_t Transport_SendPacket(const char interface, const uint8_t data_length, const int8_t* packet_data) {
  uint8_t sum = 0;//0x0a + 0x0a;

  uint8_t header[2] = {0x0a, 0x0a};
  SerialDevice_putc(header[0]);
  SerialDevice_putc(header[1]);
  
  SerialDevice_putc(interface);
  sum += interface;
  SerialDevice_putc(data_length);
  sum += data_length;

  //uint8_t sender[4] = {'U', 'A', 'R', 'T'};
  //for(uint8_t i = 0;i < 4;i++) {
    //sum += sender[i];
  //  SerialDevice_putc(sender[i]);
  //}

  for(uint8_t i = 0;i < data_length;i++) {
    sum += packet_data[i];
    SerialDevice_putc(packet_data[i]);
  }
  SerialDevice_putc(sum);
  return PACKET_HEADER_SIZE + data_length + 1;
}

/**
 * Transport_ReceivePacket
 * ¥arg packet
 * ¥arg timeout
 */
int8_t Transport_ReceivePacket(uint8_t* packet, const uint32_t& timeout) {
  uint8_t counter = 0;
  uint8_t buf;
  int8_t ret;
  while(1) {
    if((ret=SerialDevice_read(&buf, 1, timeout)) < 0) {
      return 0;
    }
    if (buf != PACKET_STARTING_CHARACTOR_0) {
      counter++;
      continue;
    }  
    if((ret=SerialDevice_read(&buf, 1, timeout)) < 0) {
      return 0;
    }
    if (buf != PACKET_STARTING_CHARACTOR_1) {
      counter++;
      continue;
    }
    break;
  }
  
   
  if((ret=SerialDevice_read(packet, PACKET_HEADER_SIZE, timeout)) < 0) {
    return ret;
  }  

  //if((ret=SerialDevice_read(packet+PACKET_HEADER_SIZE,
  //  4,
  //  timeout)) < 0) {
  //  return ret;
  //}

  if((ret=SerialDevice_read(packet+PACKET_HEADER_SIZE,
    packet[DATA_LENGTH],
    timeout)) < 0) {
    return ret;
  }
  
  if((ret=SerialDevice_read(&buf, 1, timeout)) < 0) {
    return ret;
  }
  
  uint8_t sum = 0;//PACKET_STARTING_CHARACTOR_0 + PACKET_STARTING_CHARACTOR_1;
  for(uint8_t i = 0;i < PACKET_HEADER_SIZE+packet[DATA_LENGTH];i++) {
    sum += packet[i];
  }
  if(buf != sum) {
    return -CHECKSUM_ERROR;
  }
  return PACKET_HEADER_SIZE + packet[DATA_LENGTH];
}
