#include <Arduino.h>

#include "NullBuffer.h"


NullBuffer::NullBuffer()
{
  m_pData = NULL;
  m_Size = 0;
  isUpdated = 0;
}


NullBuffer::~NullBuffer()
{

}


void NullBuffer::push(const char* pData, int size)
{
  if(size != m_Size) {
    free(m_pData);
    m_pData = (char*)malloc(size);
    m_Size = size;
  }
  memcpy(m_pData, pData, size);
  isUpdated = 1;
}

void NullBuffer::pop(char* pData, int size) 
{
  if(size >= m_Size) {
    memcpy(pData, m_pData, m_Size);
  }
  isUpdated = 0;
}

int NullBuffer::getNextDataSize()
{
  return m_Size;
}

int NullBuffer::hasNext() {
  return isUpdated;
}
