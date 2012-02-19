#define RTNO_SUBMODULE_DEFINE
#include <stdint.h>
#include <Arduino.h>

#include "PacketBuffer.h"
#include "Transport.h"
#include "Packet.h"

char m_SenderInfo[4];

#define SENDER_INFO_SIZE 4

int8_t Transport_init()
{

}

int8_t Transport_SendPacket(const char* destination)
{
  uint8_t size = PacketBuffer_getPacketSize();
  int8_t* pData = PacketBuffer_getBuffer();
  SerialDevice_write(pData, size);
}


int8_t Transport_ReceivePacket()
{
  uint8_t counter = 0;
  uint8_t sum = 0;
  PacketBuffer_clear();
  int8_t* packet = PacketBuffer_getBuffer();

  if(SerialDevice_receive() <= 0) {
    return 0;
  }

  while(SerialDevice_available() < PACKET_HEADER_SIZE) {
    delayMicroseconds(PACKET_WAITING_DELAY);
    counter++;
    if(counter == PACKET_WAITING_COUNT) {
      return -TIMEOUT;
    }
  }
  SerialDevice_read(packet, PACKET_HEADER_SIZE);
  PacketBuffer_seek(PACKET_HEADER_SIZE);

  counter = 0;
  while(SerialDevice_available() < packet[DATA_LENGTH] + 1) {
    delayMicroseconds(PACKET_WAITING_DELAY);
    counter++;
    if(counter == PACKET_WAITING_COUNT) {
      return -DATA_TIMEOUT;
    }
  }
  SerialDevice_read(packet + PACKET_HEADER_SIZE, packet[DATA_LENGTH] + 1);
  PacketBuffer_seek(packet[DATA_LENGTH]+1);

  for(uint8_t i = 0;i < PACKET_HEADER_SIZE + packet[DATA_LENGTH];i++) {
    sum += ((uint8_t*)packet)[i];
  }
  
  if(sum != ((uint8_t*)packet)[PACKET_HEADER_SIZE + packet[DATA_LENGTH]]) {
    return -CHECKSUM_ERROR;
  }

  return PACKET_HEADER_SIZE + packet[DATA_LENGTH] + 1;
}

/*
int8_t Transport_ReceivePacket(int8_t* packet, char from[]) {
  uint8_t counter = 0;
  uint8_t sum = 0;

  if(SerialDevice_receive() <= 0) {
    return 0;
  }

  while(SerialDevice_available() < PACKET_HEADER_SIZE + SENDER_INFO_SIZE) {
    delayMicroseconds(PACKET_WAITING_DELAY);
    counter++;
    if(counter == PACKET_WAITING_COUNT) {
      return -TIMEOUT;
    }
  }
  SerialDevice_read(packet+INTERFACE, PACKET_HEADER_SIZE);
  //  packet[INTERFACE] = SerialDevice_getc();
  sum += packet[INTERFACE];
  //  packet[DATA_LENGTH] = SerialDevice_getc();
  sum += packet[DATA_LENGTH];
  for(uint8_t i = 0;i < SENDER_INFO_SIZE;i++) {
    from[i] = SerialDevice_getc();
    sum += from[i];
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
  
  counter = 0;
  while(SerialDevice_available() == 0) {
    delayMicroseconds(PACKET_WAITING_DELAY);
    counter++;
    if(counter == PACKET_WAITING_COUNT) {
      return -DATA_TIMEOUT;
    }
  }
  uint8_t checksum = SerialDevice_getc();
  
  if(sum != checksum) {
    return -CHECKSUM_ERROR;
  }
  return PACKET_HEADER_SIZE + packet[DATA_LENGTH] + 1;
}
*/
/*
int8_t Transport_SendPacket(const char interface, const uint8_t data_length, const int8_t* packet_data) {
  uint8_t sum = 0;
  
  //  uint8_t sender[4] = {'U', 'A', 'R', 'T'};
  SerialDevice_putc(interface);
  sum += interface;
  SerialDevice_putc(data_length);
  sum += data_length;

  for(uint8_t i = 0;i < SENDER_INFO_SIZE;i++) {
    sum += m_SenderInfo[i];
    SerialDevice_putc(m_SenderInfo[i]);
  }

  for(uint8_t i = 0;i < data_length;i++) {
    sum += packet_data[i];
    SerialDevice_putc(packet_data[i]);
  }
  SerialDevice_putc(sum);
  return PACKET_HEADER_SIZE + data_length + 1;
}
*/
