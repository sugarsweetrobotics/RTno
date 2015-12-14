#include <Arduino.h>
#include "EtherTcp.h"
#include <SPI.h>
#include <Ethernet.h>

static EthernetServer *m_pServer;
static EthernetClient *m_pClient;

void EtherTcp_init(uint8_t* mac, uint8_t* ip, 
		   uint8_t* gateway, uint8_t* subnet,
		   uint16_t port) 

{
  Ethernet.begin(mac, ip, gateway, gateway, subnet);
  m_pServer = new EthernetServer(port);

  SerialDevice_available = EtherTcp_available;
  SerialDevice_getc = EtherTcp_getc;
  SerialDevice_putc = EtherTcp_putc;

  m_pServer->begin();
  m_pClient = new EthernetClient();
  *m_pClient = m_pServer->available();
 
}

uint8_t EtherTcp_available()
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

uint8_t EtherTcp_getc()
{
  return m_pClient->read();
}
