#include <Arduino.h>
#include "EtherTcp.h"
#include <../SPI/SPI.h>
#include <../Ethernet/Ethernet.h>

static EthernetServer *m_pServer;
static EthernetClient *m_pClient;


int8_t EtherTcp_receive(int8_t* sourceInfo);
int8_t EtherTcp_write(const int8_t* target, const int8_t* src, const uint8_t size);
uint8_t EtherTcp_read(int8_t* dst, const uint8_t size);
void EtherTcp_putc(const char c);
uint8_t EtherTcp_available();
char EtherTcp_getc();


void EtherTcp_init(uint8_t* mac, uint8_t* ip, 
		   uint8_t* gateway, uint8_t* subnet,
		   uint16_t port) 

{
  Ethernet.begin(mac, ip, gateway, gateway, subnet);
  m_pServer = new EthernetServer(port);

  SerialDevice_available = EtherTcp_available;
  SerialDevice_read      = EtherTcp_read;
  SerialDevice_write     = EtherTcp_write;
  SerialDevice_receive   = EtherTcp_receive;

  m_pServer->begin();
  m_pClient = new EthernetClient();
  *m_pClient = m_pServer->available();
}

int8_t EtherTcp_receive(int8_t* sourceInfo) {
  memcpy(sourceInfo, "ETCP", 4);
  return EtherTcp_available();
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

uint8_t EtherTcp_read(int8_t* dst, const uint8_t size) {
  while(EtherTcp_available() <= 0);
  for(int i = 0;i < size;i++) {
    dst[i] = m_pClient->read();
  }
  return size;
}

int8_t EtherTcp_write(const int8_t* target, const int8_t*src, const uint8_t size) {
  //  if(strncmp((const char*)target, "ETCP", 4) != 0) return -1;
  if(*m_pClient) {
    return m_pClient->write((const uint8_t*)src, size);
  }
  return 0;
}

/*
void EtherTcp_putc(const char c) {
  m_pServer->write(c);
}

char EtherTcp_getc()
{
  return m_pClient->read();
}
*/
