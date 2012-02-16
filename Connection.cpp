#include <stdint.h>
#include "Connection.h"

static uint8_t m_ConnectionIteratorCounter;

void Connection_init(void)
{

}

uint8_t Connection_isConnected(char* senderInfo)
{
  return 1;
}

void Connection_create(char* senderInfo)
{

}

void Connection_destroy(char* senderInfo)
{

}

void ConnectionIterator_init(PortBase* pPort)
{
  m_ConnectionIteratorCounter = 0;
}

uint8_t ConnectionIterator_hasNext()
{
  return m_ConnectionIteratorCounter == 0 ? 1 : 0;
}

void ConnectionIterator_next() {
  m_ConnectionIteratorCounter++;
}

