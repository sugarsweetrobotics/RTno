#include <Arduino.h>
#include "EtherTcp.h"
#include <../SPI/SPI.h>
#include <../Ethernet/Ethernet.h>

static EthernetServer *m_pServer;
static EthernetClient *m_pClient;

void EtherTcp_init(uint8_t* mac, uint8_t* ip, 
		   uint8_t* gateway, uint8_t* subnet,
		   uint16_t port) 

{
  /*
  Serial.print("MAC=");
  Serial.print(mac[0], HEX), Serial.print(",");
  Serial.print(mac[1], HEX), Serial.print(",");
  Serial.print(mac[2], HEX), Serial.print(",");
  Serial.print(mac[3], HEX), Serial.print(",");
  Serial.print(mac[4], HEX), Serial.print(",");
  Serial.println(mac[5], HEX);


  Serial.print("IP=");
  Serial.print(ip[0], DEC), Serial.print(",");
  Serial.print(ip[1], DEC), Serial.print(",");
  Serial.print(ip[2], DEC), Serial.print(",");
  Serial.println(ip[3], DEC);

  Serial.print("SUBNET=");
  Serial.print(subnet[0], DEC), Serial.print(",");
  Serial.print(subnet[1], DEC), Serial.print(",");
  Serial.print(subnet[2], DEC), Serial.print(",");
  Serial.println(subnet[3], DEC);

  Serial.print("GATEWAY=");
  Serial.print(gateway[0], DEC), Serial.print(",");
  Serial.print(gateway[1], DEC), Serial.print(",");
  Serial.print(gateway[2], DEC), Serial.print(",");
  Serial.println(gateway[3], DEC);
  */
  
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

char EtherTcp_getc()
{
  return m_pClient->read();
}
