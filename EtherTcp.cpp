#include <Arduino.h>
#include "EtherTcp.h"

EtherTcp::EtherTcp(byte* mac, byte* ip, 
		   byte* gateway, byte* subnet, 
		   unsigned short port) 
{
  unsigned char dns[] = {192,168,42,254};
  Ethernet.begin(mac, ip, dns, gateway, subnet);
  m_pServer = new EthernetServer(port);
  m_pServer->begin();
  m_Client = m_pServer->available();
}

EtherTcp::~EtherTcp()
{


}

int EtherTcp::available()
{

  if(m_Client) {
    return m_Client.available();
  } else {
    m_Client = m_pServer->available();
    if(m_Client) {
      return m_Client.available();
    }
  }
  return 0;
}


void EtherTcp::write(const void* data, int size)
{
  for(int i = 0;i < size;i++) {
    m_pServer->write(*(((const unsigned char*)data)+i));
  }
}

int EtherTcp::read()
{
  return m_Client.read();
}
