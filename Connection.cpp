#include <Arduino.h>
#include <stdint.h>
#include "Packet.h"
#include <string.h>
#include "Connection.h"

Connection* Connection_create(int8_t* targetAddress, uint8_t targetPort)
{
  Connection* buf = (Connection*)malloc(sizeof(Connection));
  memcpy(buf->targetAddress, targetAddress, PKT_SOURCE_ADDR_SIZE);
  buf->targetPort = targetPort;
  return buf;
}

void Connection_destroy(char* senderInfo)
{
  free(senderInfo);
}

ConnectionList* ConnectionList_create(uint8_t size) {
  ConnectionList* list = (ConnectionList*)malloc(sizeof(ConnectionList));
  if(list == NULL) {
    return NULL;
  }
  list->length = 0;
  list->listLength = size;
  if(size == 0) {
    list->data = NULL;
  } else {
    list->data = (Connection**)malloc(sizeof(Connection*)*size);
    if(list->data == NULL) {
      free(list);
      return NULL;
    }
  }
  return list;
}

void ConnectionList_destroy(ConnectionList *list)
{
  free(list->data);
  free(list);
}

int8_t ConnectionList_addConnection(ConnectionList* list, Connection* connection)
{
  if(list->length == list->listLength) {
    Connection** buffer = (Connection**)malloc(sizeof(Connection*) * (list->length + 1));
    if(buffer == NULL) {
      return -1;
    }
    for(int i = 0;i < list->length;i++) {
      buffer[i] = list->data[i];
    }
    free(list->data);
    list->data = buffer;
    list->listLength++;
  }

  list->data[list->length] = connection;
  list->length++;
  return 0;
}


int ConnectionList_searchIndex(ConnectionList* list, int8_t targetAddress[], uint8_t targetPort) {
  for(int i = 0;i < list->length;i++) {
    if( strncmp((const char*)list->data[i]->targetAddress, (const char*)targetAddress, PKT_SOURCE_ADDR_SIZE) == 0 ) {
      if(list->data[i]->targetPort == targetPort) {
	return i;
      }
    }
  }
  return -1;
}

Connection* ConnectionList_search(ConnectionList* list, int8_t targetAddress[], uint8_t targetPort) {
  int index = ConnectionList_searchIndex(list, targetAddress, targetPort);
  if(index < 0) {
    return NULL;
  } 
  return list->data[index];
}

int8_t ConnectionList_size(ConnectionList *list) {
  return list->length;
}

Connection* ConnectionList_item(ConnectionList* list, int8_t index) {
  if(index < 0 || index >= list->length) return NULL;
  return list->data[index];
}

void ConnectionList_remove(ConnectionList *list, Connection* connection) {
  int index = ConnectionList_searchIndex(list, connection->targetAddress, connection->targetPort);
  if(index > 0) {
    free(list->data[index]);
    list->data[index] = NULL;
  }
  
  for(int i = index+1;i < list->length;i++) {
    list->data[i-1] = list->data[i];
  }
  list->length--;
}
