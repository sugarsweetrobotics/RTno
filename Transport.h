#pragma once

#include <stdint.h>
#include "SerialDevice.h"

int8_t Transport_init();

int8_t Transport_SendPacket(const char interface, const uint8_t data_length, const int8_t* packet_data);
    
int8_t Transport_ReceivePacket(uint8_t* packet, const uint32_t &timeout=INFINITE);
