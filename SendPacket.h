/*******************************************
 * SendPacket.h
 * @author Yuki Suga
 * @copyright Yuki Suga (ysuga.net) Nov, 10th, 2010.
 * @license LGPLv3
 *****************************************/

#ifndef SEND_PACKET_HEADER_INCLUDED
#define SEND_PACKET_HEADER_INCLUDED

#include "Packet.h"

int SendPacket(const char interface, const char data_length, const char* packet_data);

#endif

