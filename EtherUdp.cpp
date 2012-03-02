#include <Arduino.h>
#include "EtherUdp.h"
#include <../SPI/SPI.h>
#include <../Ethernet/Ethernet.h>
#include <../Ethernet/EthernetUdp.h>

EthernetUDP Udp;


int8_t EtherUdp_receive(int8_t* sourceInfo);
int8_t EtherUdp_write(const int8_t* target, const int8_t* src, const uint8_t size);
uint8_t EtherUdp_read(int8_t* dst, const uint8_t size);
uint8_t EtherUdp_available();

uint16_t m_Port;
int8_t m_PacketSize;
void EtherUdp_init(uint8_t* mac, uint8_t* ip, 
		   uint8_t* gateway, uint8_t* subnet,
		   uint16_t port) 
{
  Ethernet.begin(mac, ip);//, gateway, gateway, subnet);
  Udp.begin(port);
  m_Port = port;

  SerialDevice_available = EtherUdp_available;
  SerialDevice_receive   = EtherUdp_receive;
  SerialDevice_read      = EtherUdp_read;
  SerialDevice_write     = EtherUdp_write;
}


int8_t EtherUdp_receive(int8_t* sourceInfo)
{
  m_PacketSize = Udp.parsePacket();
  if(m_PacketSize > 0) {

    for(int i = 0;i < 4;i++) {
      sourceInfo[i] = Udp.remoteIP()[i];
    }
  }
  return m_PacketSize;
}


uint8_t EtherUdp_available()
{
  return m_PacketSize;
  //  return Udp.available();
}

int8_t EtherUdp_write(const int8_t* target, const int8_t* src, const uint8_t size)
{
  uint8_t* ip = (uint8_t*)target;
  
  //Udp.beginPacket(new IPAddress(ip[0], ip[1], ip[2], ip[3]), m_Port);
  Udp.beginPacket(Udp.remoteIP(), m_Port);
  //Udp.beginPacket("192.168.42.130", m_Port);
  Udp.write((uint8_t*)src, size);
  Udp.endPacket();
  return size;
}


uint8_t EtherUdp_read(int8_t* dst, const uint8_t size)
{
  int readSize = size;
  if(m_PacketSize < size) {
    readSize = m_PacketSize;
  }

  return Udp.read((uint8_t*)dst, readSize);
}
