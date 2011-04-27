/*******************************************
 * SendPacket.cpp
 * @author Yuki Suga
 * @copyright Yuki Suga (ysuga.net) Nov, 10th, 2010.
 * @license LGPLv3
 *****************************************/

#include "Packet.h"
#include <HardwareSerial.h>
#include <WConstants.h>

int SendPacket(const char interface, const char data_length, const char* packet_data) {
  unsigned char sum = 0;
  Serial.write((const uint8_t*)&interface, 1);
  sum += interface;
  Serial.write((const uint8_t*)&data_length, 1);
  sum += data_length;
  for(int i = 0;i < data_length;i++) {
    sum += packet_data[i];
    Serial.write((const uint8_t*)packet_data+i, 1);
  }
  //  if(data_length != 0) {
  //n    Serial.write((const uint8_t*)packet_data, data_length);
  //  }
  //sum = 32;
  Serial.write((const uint8_t*)&sum, 1);
  return PACKET_HEADER_SIZE + data_length + 1;
}
