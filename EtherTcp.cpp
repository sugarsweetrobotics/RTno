#include <Arduino.h>
#include "EtherTcp.h"
#include <../SPI/SPI.h>
#include <../Ethernet/Ethernet.h>

static EthernetServer *m_pServer;
static EthernetClient *m_pClient;

void EtherTcp_init(byte* mac, byte* ip, 
		   byte* gateway, byte* subnet, 
		   unsigned short port) 
{
  unsigned char dns[] = {192,168,42,254};
  Ethernet.begin(mac, ip, dns, gateway, subnet);
  m_pServer = new EthernetServer(port);
  m_pServer->begin();
  m_pClient = new EthernetClient();
  *m_pClient = m_pServer->available();

  SerialDevice_available = EtherTcp_available;
  SerialDevice_getc = EtherTcp_getc;
  SerialDevice_putc = EtherTcp_putc;
}

unsigned char EtherTcp_available()
{
  if(*m_pClient) {
    return m_pClient->available();
  } else {
    *m_pClient = m_pServer->available();
    if(*m_pClient) {
      return m_pClient->available();
    }
  }
  return 0;
}


void EtherTcp_putc(const char c) {
  m_pServer->write(c);
}
/*
d EtherTcp::write(const void* data, int size)
{
  for(int i = 0;i < size;i++) {
    m_pServer->write(*(((const unsigned char*)data)+i));
  }
  }*/

char EtherTcp_getc()
{
  return m_pClient->read();
}
