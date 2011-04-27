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


int OutPort::write()
{
  int datalen = GetLength() * SizeofData();
  int namelen = strlen(GetName());
  char packet_buffer[MAX_PACKET_SIZE];
  packet_buffer[0] = namelen;
  packet_buffer[1] = datalen;
  memcpy(&(packet_buffer[2]), GetName(), namelen);
  memcpy(&(packet_buffer[2 + namelen]), GetBuffer(), datalen);
  SendPacket(OUTPORT_WRITE, 2+namelen+datalen, packet_buffer);
  ReceivePacket(packet_buffer);
  return PACKET_HEADER_SIZE+2+namelen+datalen;
}
