#ifndef ETHER_UDP_HEADER_INCLUDED
#define ETHER_UDP_HEADER_INCLUDED

#include <stdint.h>
#include "SerialDevice.h"
void EtherUdp_init(uint8_t* mac, uint8_t* ip, 
		   uint8_t* gateway, uint8_t* subnet,
		   uint16_t port) ;





#endif ///#ifndef ETHER_UDP_HEADER_INCLUDED