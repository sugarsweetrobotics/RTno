#include <Arduino.h>

#include "Transport.h"
#include "Packet.h"




int Transport::SendPacket(const char interface, const char data_length, const char* packet_data) {
  unsigned char sum = 0;
  unsigned char sender[4] = {'U', 'A', 'R', 'T'};
  m_pSerialDevice->write((const uint8_t*)&interface, 1);
  sum += interface;
  m_pSerialDevice->write((const uint8_t*)&data_length, 1);
  sum += data_length;

  for(int i = 0;i < 4;i++) {
    sum += sender[i];
    m_pSerialDevice->write((const uint8_t*)sender+i, 1);
  }

  for(int i = 0;i < data_length;i++) {
    sum += packet_data[i];
    m_pSerialDevice->write((const uint8_t*)packet_data+i, 1);
  }
  m_pSerialDevice->write((const uint8_t*)&sum, 1);
  return PACKET_HEADER_SIZE + data_length + 1;
}

int Transport::ReceivePacket(unsigned char* packet) {
  int counter = 0;
  unsigned char sum = 0;

  if(m_pSerialDevice->available() == 0) {
    return 0;
  }

  while(m_pSerialDevice->available() < PACKET_HEADER_SIZE) {
    delayMicroseconds(PACKET_WAITING_DELAY);
    counter++;
    if(counter == PACKET_WAITING_COUNT) {
      return -TIMEOUT;
    }
  }
  packet[INTERFACE] = m_pSerialDevice->read();
  sum += packet[INTERFACE];
  packet[DATA_LENGTH] = m_pSerialDevice->read();
  sum += packet[DATA_LENGTH];

  counter = 0;
  while(m_pSerialDevice->available() < 4) {
    delayMicroseconds(PACKET_WAITING_DELAY);
    counter++;
    if(counter == PACKET_WAITING_COUNT) {
      return -TIMEOUT;
    }
  }
  for(int i = 0;i < 4;i++) {
    unsigned char val = m_pSerialDevice->read();
    sum += val;
  }

  for(int i = 0;i < packet[DATA_LENGTH];i++) {
    counter = 0;
    while(m_pSerialDevice->available() == 0) {
      delayMicroseconds(PACKET_WAITING_DELAY);
      counter++;
      if(counter == PACKET_WAITING_COUNT) {
	return -DATA_TIMEOUT;
      }
    }
    packet[PACKET_HEADER_SIZE+i] = m_pSerialDevice->read();
    sum += packet[PACKET_HEADER_SIZE+i];
  }
  
  while(m_pSerialDevice->available() == 0) {
    ;
  }
  unsigned char checksum = m_pSerialDevice->read();
  
  if(sum != checksum) {
    return -CHECKSUM_ERROR;
  }
  return PACKET_HEADER_SIZE + packet[DATA_LENGTH] + 1;
}
