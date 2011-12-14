/*******************************************
 * OutPort.cpp
 * @author Yuki Suga
 * @copyright Yuki Suga (ysuga.net) Nov, 10th, 2010.
 * @license LGPLv3
 *****************************************/

#include <string.h>
#include "BasicDataType.h"
#include "OutPort.h"
#include "SendPacket.h"
#include "ReceivePacket.h"

OutPort::OutPort(char* name, TimedBoolean& Data) :
  OutPortBase(name)
{
  //  m_pData = pData;
  m_pData = &Data;
  m_TypeCode = 'b';
}

OutPort::OutPort(char* name, TimedChar& Data) :
  OutPortBase(name)
{
  //  m_pData = pData;
  m_pData = &Data;
  m_TypeCode = 'c';
}

OutPort::OutPort(char* name, TimedOctet& Data) :
  OutPortBase(name)
{
  //  m_pData = pData;
  m_pData = &Data;
  m_TypeCode = 'o';
}

OutPort::OutPort(char* name, TimedLong& Data) :
  OutPortBase(name)
{
  //  m_pData = pData;
  m_pData = &Data;
  m_TypeCode = 'l';
}

OutPort::OutPort(char* name, TimedFloat& Data) :
  OutPortBase(name)
{
  //  m_pData = pData;
  m_pData = &Data;
  m_TypeCode = 'f';
}

OutPort::OutPort(char* name, TimedDouble& Data) :
  OutPortBase(name)
{
  //  m_pData = pData;
  m_pData = &Data;
  m_TypeCode = 'd';
}

OutPort::OutPort(char* name, TimedBooleanSeq& Data) :
  OutPortBase(name)
{
  //  m_pData = pData;
  m_pData = &Data;
  m_TypeCode = 'B';
}

OutPort::OutPort(char* name, TimedCharSeq& Data) :
  OutPortBase(name)
{
  //  m_pData = pData;
  m_pData = &Data;
  m_TypeCode = 'C';
}

OutPort::OutPort(char* name, TimedOctetSeq& Data) :
  OutPortBase(name)
{
  //  m_pData = pData;
  m_pData = &Data;
  m_TypeCode = 'O';
}


OutPort::OutPort(char* name, TimedLongSeq& Data) :
  OutPortBase(name)
{
  //  m_pData = pData;
  m_pData = &Data;
  m_TypeCode = 'L';
}

OutPort::OutPort(char* name, TimedFloatSeq& Data) :
  OutPortBase(name)
{
  //  m_pData = pData;
  m_pData = &Data;
  m_TypeCode = 'F';
}

OutPort::OutPort(char* name, TimedDoubleSeq& Data) :
  OutPortBase(name)
{
  //  m_pData = pData;
  m_pData = &Data;
  m_TypeCode = 'D';
}

OutPort::~OutPort()
{

}

int OutPort::SizeofData() {
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

int OutPort::write()
{
  //  int datalen = GetLength() * SizeofData();
  //  int namelen = strlen(GetName());
  //  char packet_buffer[MAX_PACKET_SIZE];
  //  packet_buffer[0] = namelen;
  //  packet_buffer[1] = datalen;
  //  memcpy(&(packet_buffer[2]), GetName(), namelen);
  //  memcpy(&(packet_buffer[2 + namelen]), GetBuffer(), datalen);
  //  push(packet_buffer, datalen);
  push((const char*)GetBuffer(), GetLength() * SizeofData());
  //  SendPacket(OUTPORT_WRITE, 2+namelen+datalen, packet_buffer);
  //  ReceivePacket(packet_buffer);
  return GetLength();//PACKET_HEADER_SIZE+2+namelen+datalen;
}
