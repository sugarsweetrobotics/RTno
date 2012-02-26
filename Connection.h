#ifndef CONNECTION_HEADER_INCLUDED
#define CONNECTION_HEADER_INCLUDED

#include "Packet.h"
typedef struct __Connection {
  int8_t targetAddress[PKT_SOURCE_ADDR_SIZE];
  uint8_t targetPort;
} Connection;

Connection* Connection_create(int8_t* targetAddress, uint8_t targetPort);
void Connection_destroy(Connection *pConnection);


typedef struct __ConnectionList {
  uint8_t listLength;
  uint8_t length;
  Connection** data;
} ConnectionList;

ConnectionList* ConnectionList_create(uint8_t initialSize);
void ConnectionList_destroy();
int8_t ConnectionList_addConnection(ConnectionList* list, Connection* connection);
Connection* ConnectionList_search(ConnectionList* list, int8_t targetAddress[], uint8_t targetPort);
void ConnectionList_remove(ConnectionList* list, Connection* connection);
int8_t ConnectionList_size(ConnectionList* list);
Connection* ConnectionList_item(ConnectionList* list, int8_t index);
#endif
