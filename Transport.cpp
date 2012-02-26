#define RTNO_SUBMODULE_DEFINE
#include <stdint.h>
#include <Arduino.h>

#include "PacketBuffer.h"
#include "Transport.h"
#include "Packet.h"

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

  while(SerialDevice_available() < PKT_HEADER_SIZE) {
    delayMicroseconds(PACKET_WAITING_DELAY);
    counter++;
    if(counter == PACKET_WAITING_COUNT) {
      return RTNO_RTC_PACKET_TIMEOUT;
    }
  }
  SerialDevice_read(packet, PKT_HEADER_SIZE);
  PacketBuffer_seek(PKT_HEADER_SIZE);

  counter = 0;
  while(SerialDevice_available() < packet[PKT_ADDR_DATA_LENGTH] + 1) {
    delayMicroseconds(PACKET_WAITING_DELAY);
    counter++;
    if(counter == PACKET_WAITING_COUNT) {
      return RTNO_RTC_PACKET_TIMEOUT;
    }
  }
  SerialDevice_read(packet + PKT_HEADER_SIZE, packet[PKT_ADDR_DATA_LENGTH] + 1);
  PacketBuffer_seek(packet[PKT_ADDR_DATA_LENGTH]+1);

  for(uint8_t i = 0;i < PKT_HEADER_SIZE + packet[PKT_ADDR_DATA_LENGTH];i++) {
    sum += ((uint8_t*)packet)[i];
  }
  
  if(sum != ((uint8_t*)packet)[PKT_HEADER_SIZE + packet[PKT_ADDR_DATA_LENGTH]]) {
    return RTNO_RTC_CHECKSUM_ERROR;
  }

  return PKT_HEADER_SIZE + packet[PKT_ADDR_DATA_LENGTH] + 1;
}
