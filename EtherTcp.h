#ifndef ETHER_TCP_HEADER_INCLUDED
#define ETHER_TCP_HEADER_INCLUDED



#include "SerialDevice.h"
//#include "../SPI/SPI.h"
//#include "../Ethernet/Ethernet.h"

void EtherTcp_init(byte *mac, byte *ip, byte *gateway, byte *subnet, unsigned short port);

void EtherTcp_putc(const char c);
unsigned char EtherTcp_available();
char EtherTcp_getc();


#if 0
class EtherTcp : public SerialDevice {
 private:

 protected:
  EthernetServer *m_pServer;
  EthernetClient m_Client;
 public:
  EtherTcp(byte *mac, byte *ip, byte *gateway, byte *subnet, unsigned short port);
  virtual ~EtherTcp();


 public:
  virtual void write(const void* data, int size);
  virtual int available();

  virtual int read();
};
#endif

#endif // #ifndef ETHER_HEADER_INCLUDED
