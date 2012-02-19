#include "Packet.h"
#include <Arduino.h>
#include"PacketBuffer.h"


static int8_t* m_pBuffer;
static uint8_t m_Size;
static uint8_t m_Counter;

void PacketBuffer_init(uint8_t size) {
  if(size > m_Size) {
    free(m_pBuffer);
    m_pBuffer = (int8_t*)malloc(size);
    m_Size = size;
  }
  m_Counter = 0;
}

void PacketBuffer_clear() {
  m_Counter = 0;
}

void PacketBuffer_seek(uint8_t forward) {
  m_Counter += forward;
}

void PacketBuffer_seal() {
  m_pBuffer[DATA_LENGTH] = m_Counter;
  uint8_t sum = 0;
  m_pBuffer[DATA_START_ADDR+m_Counter] = 0;
  for(unsigned int i = 0;i < DATA_START_ADDR+m_Counter;i++) {
    sum += m_pBuffer[i];
  }
  m_pBuffer[DATA_START_ADDR+m_Counter] |= sum;
}



void PacketBuffer_setInterface(int8_t interface_c) {
  m_pBuffer[INTERFACE] = interface_c;
}

int8_t PacketBuffer_getInterface() {
  return m_pBuffer[INTERFACE];
}


void PacketBuffer_setAddress(int8_t* address) {
  for(unsigned int i = 0;i < 4;i++) {
    m_pBuffer[SOURCE_ADDR+i] = address[i];
  }
}

int8_t* PacketBuffer_getAddress() {
  return &(m_pBuffer[SOURCE_ADDR]);
}


void PacketBuffer_setTargetPortIndex(int8_t index) {
  m_pBuffer[TARGET_PORT] = index;

}

void PacketBuffer_setSourcePortIndex(int8_t index) {
  m_pBuffer[SOURCE_PORT] = index;
}

int8_t PacketBuffer_getTargetPortIndex() {
  return m_pBuffer[TARGET_PORT];
}

int8_t PacketBuffer_getSourcePortIndex() {
  return m_pBuffer[SOURCE_PORT];
}


void PacketBuffer_push(const int8_t* src, uint8_t size) {
  for(unsigned int i = 0;i < size;i++) {
    m_pBuffer[DATA_START_ADDR+m_Counter] = src[i];
    m_Counter++;
  }
}


uint8_t PacketBuffer_getReceivedPacketSize() {
  return m_pBuffer[DATA_LENGTH];
}

uint8_t PacketBuffer_getPacketSize() {
  return PACKET_HEADER_SIZE + m_Counter + 1;
}

int8_t* PacketBuffer_getBuffer() {
  return m_pBuffer;
}

int8_t* PacketBuffer_getDataBuffer() {
  return m_pBuffer + DATA_START_ADDR;
}
