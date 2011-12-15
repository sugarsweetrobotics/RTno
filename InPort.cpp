/*******************************************
 * InPort.cpp
 * @author Yuki Suga
 * @copyright Yuki Suga (ysuga.net) Nov, 10th, 2010.
 * @license LGPLv3
 *****************************************/


#include <string.h>
#include "Packet.h"
#include "BasicDataType.h"
#include "InPort.h"

InPort::InPort(char* name, TimedOctet& Data):
  InPortBase(name)
{
  m_pData = &Data;
  m_TypeCode = 'o';
}

InPort::InPort(char* name, TimedChar& Data):
  InPortBase(name)
{
  m_pData = &Data;
  m_TypeCode = 'c';
}

InPort::InPort(char* name, TimedBoolean& Data):
  InPortBase(name)
{
  m_pData = &Data;
  m_TypeCode = 'b';
}


InPort::InPort(char* name, TimedDouble& Data):
  InPortBase(name)
{
  m_pData = &Data;
  m_TypeCode = 'd';
}

InPort::InPort(char* name, TimedFloat& Data):
  InPortBase(name)
{
  m_pData = &Data;
  m_TypeCode = 'f';
}

InPort::InPort(char* name, TimedLong& Data):
  InPortBase(name)
{
  m_pData = &Data;
  m_TypeCode = 'l';
}

InPort::InPort(char* name, TimedOctetSeq& Data):
  InPortBase(name)
{
  m_pData = &Data;
  m_TypeCode = 'O';
}

InPort::InPort(char* name, TimedCharSeq& Data):
  InPortBase(name)
{
  m_pData = &Data;
  m_TypeCode = 'C';
}

InPort::InPort(char* name, TimedBooleanSeq& Data):
  InPortBase(name)
{
  m_pData = &Data;
  m_TypeCode = 'B';
}



InPort::InPort(char* name, TimedDoubleSeq& Data):
  InPortBase(name)
{
  m_pData = &Data;
  m_TypeCode = 'D';
}


InPort::InPort(char* name, TimedFloatSeq& Data):
  InPortBase(name)
{
  m_pData = &Data;
  m_TypeCode = 'F';
}

InPort::InPort(char* name, TimedLongSeq&Data):
  InPortBase(name)
{
  m_pData = &Data;
  m_TypeCode = 'L';
}

InPort::~InPort()
{
}

int InPort::isNew() {
  return hasNext();
}

int InPort::read() {
  int len = getNextDataSize();
  SetLength(len / SizeofData());
  void* pBuffer = GetBuffer();
  pop((char*)pBuffer, len);
  return len;

  /*
  char packet_buffer[MAX_PACKET_SIZE];
  SendPacket(INPORT_READ, strlen(GetName()), GetName());
  ReceivePacket(packet_buffer);
  if(packet_buffer[INTERFACE] != INPORT_READ) {
    return -INVALID_PACKET_INTERFACE;
  }
  int len = packet_buffer[DATA_LENGTH] / SizeofData();
  int isSequence = isSequenceType();
  SetLength(len);
  void *pBuffer = GetBuffer();
  memcpy(pBuffer, &(packet_buffer[DATA_START_ADDR]), len*SizeofData());
  return len;
  */
}


int InPort::SizeofData() {
  switch(m_TypeCode) {
  case 'b':
  case 'B':
  case 'o':
  case 'O':
  case 'c':
  case 'C':
    return 1;
  default:
    return 4;
  }
}
  
