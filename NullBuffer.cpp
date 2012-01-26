#include <Arduino.h>

#include "NullBuffer.h"

struct NullBuffer_private {
  char *pData;
  int size;
  int isUpdated;
};

void NullBuffer_push(PortBuffer* _this, const char* data, int size);
void NullBuffer_pop(PortBuffer* _this, char* dst, int size);
int NullBuffer_getNextDataSize(PortBuffer* _this);
int NullBuffer_hasNext(PortBuffer* _this);


PortBuffer* NullBuffer_create() 
{
  struct NullBuffer_private* privateData = 
    (struct NullBuffer_private*)malloc(sizeof(struct NullBuffer_private));

  privateData->pData = NULL;
  privateData->size = 0;
  privateData->isUpdated = 0;
  PortBuffer* retval = (PortBuffer*)malloc(sizeof(PortBuffer));
  retval->push = NullBuffer_push;
  retval->pop = NullBuffer_pop;
  retval->getNextDataSize = NullBuffer_getNextDataSize;
  retval->hasNext = NullBuffer_hasNext;
  retval->privateData = (void*)privateData;
  return retval;
}

void NullBuffer_destroy(PortBuffer* _this) {
  struct NullBuffer_private* nullBuffer = 
    (struct NullBuffer_private*)(_this->privateData);
  free(nullBuffer->pData);
  free(nullBuffer);
  free(_this);
}

void NullBuffer_push(PortBuffer* _this, const char* data, int size) {
  struct NullBuffer_private* nullBuffer = 
    (struct NullBuffer_private*)(_this->privateData);
  if(size != nullBuffer->size) {
    free(nullBuffer->pData);
    nullBuffer->pData = (char*)malloc(size);
    nullBuffer->size = size;
  }
  memcpy(nullBuffer->pData, data, size);
  nullBuffer->isUpdated = 1;
}

void NullBuffer_pop(PortBuffer* _this, char* dst, int size)
{
  struct NullBuffer_private* nullBuffer = 
    (struct NullBuffer_private*)(_this->privateData);
  if(nullBuffer->size <= size) {
    memcpy(dst, nullBuffer->pData, nullBuffer->size);
  }
  nullBuffer->isUpdated = 0;
}

int NullBuffer_getNextDataSize(PortBuffer* _this){
  return ((struct NullBuffer_private*)(_this->privateData))->size;
}

int NullBuffer_hasNext(PortBuffer* _this) {
  return ((struct NullBuffer_private*)(_this->privateData))->isUpdated;
}

