#ifndef CONNECTION_HEADER_INCLUDED
#define CONNECTION_HEADER_INCLUDED

#include "PortBase.h"

void Connection_init(void);

uint8_t Connection_isConnected(char* senderInfo);

void Connection_create(char* senderInfo);

void Connection_destroy(char* senderInfo);

void ConnectionIterator_init(PortBase* pPort);

uint8_t ConnectionIterator_hasNext();

void ConnectionIterator_next();
#endif
