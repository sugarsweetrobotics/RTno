#ifndef TRANSPORT_HEADER_INCLUDED
#define TRANSPORT_HEADER_INCLUDED

#include <stdint.h>
#include "SerialDevice.h"

int8_t Transport_init();

/**
 * Transport Packet Data.
 * The Packet Data is loaded from PacketBuffer module.
 * @param destination destination address information
 * @return zero if success. Negative if failed.
 */
int8_t Transport_SendPacket(const int8_t* destination);	
int8_t Transport_ReceivePacket(int8_t* packet, char from[]);
int8_t Transport_ReceivePacket();

#endif
