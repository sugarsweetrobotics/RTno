/*******************************************
 * ReceivePacket.h
 * @author Yuki Suga
 * @copyright Yuki Suga (ysuga.net) Nov, 10th, 2010.
 * @license LGPLv3
 *****************************************/

#include "ReceivePacket.h"
#include <HardwareSerial.h>
#include <WConstants.h>

int ReceivePacket(char* packet) {
  int counter = 0;
  unsigned char sum = 0;
  while(Serial.available() < PACKET_HEADER_SIZE) {
    delayMicroseconds(PACKET_WAITING_DELAY);
    counter++;
    if(counter == PACKET_WAITING_COUNT) {
      return -TIMEOUT;
    }
  }
  //    char host = Serial.read();
  //    char target = Serial.read();
  packet[INTERFACE] = Serial.read();
  sum += packet[INTERFACE];
  packet[DATA_LENGTH] = Serial.read();
  sum += packet[DATA_LENGTH];

  while(Serial.available() < packet[DATA_LENGTH]+1) {
    delayMicroseconds(PACKET_WAITING_DELAY);
    counter++;
    if(counter == PACKET_WAITING_COUNT) {
      return -DATA_TIMEOUT;
    }
  }

  for(int i = 0;i < packet[DATA_LENGTH];i++) {
    packet[PACKET_HEADER_SIZE+i] = Serial.read();
    sum += packet[PACKET_HEADER_SIZE+i];
  }
  packet[PACKET_HEADER_SIZE+packet[DATA_LENGTH]] = Serial.read();
  if(sum != packet[PACKET_HEADER_SIZE+packet[DATA_LENGTH]]) {
    return -CHECKSUM_ERROR;
  }
  return PACKET_HEADER_SIZE + packet[DATA_LENGTH] + 1;
}

/*
int read_string(char* buffer, int flag=1) {
  int counter = 0;
  for(int i = 0;i < 100;i++) {
    if(Serial.available() > 0) {
      buffer[counter] = Serial.read();
      if(buffer[counter] == '^') {
	buffer[counter] = 0;
	Serial.print("AO^");
	return counter+1;
      }
      counter++;
    } 
    delayMicroseconds(100);
  }
  if(flag)
  Serial.print("AE^");
  return -1;
}

*/
