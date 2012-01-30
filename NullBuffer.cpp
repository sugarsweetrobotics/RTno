#include <stdint.h>
#include <Arduino.h>

#include "NullBuffer.h"

struct NullBuffer_private {
  int8_t *pData;
  uint8_t size;
  uint8_t isUpdated;
};

void NullBuffer_push(PortBuffer* _this, const int8_t* data, uint8_t size);
void NullBuffer_pop(PortBuffer* _this, int8_t* dst, uint8_t size);
uint8_t NullBuffer_getNextDataSize(PortBuffer* _this);
uint8_t NullBuffer_hasNext(PortBuffer* _this);


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

void NullBuffer_push(PortBuffer* _this, const int8_t* data, uint8_t size) {
  struct NullBuffer_private* nullBuffer = 
    (struct NullBuffer_private*)(_this->privateData);
  if(size != nullBuffer->size) {
    free(nullBuffer->pData);
    nullBuffer->pData = (int8_t*)malloc(size);
    nullBuffer->size = size;
  }
  memcpy(nullBuffer->pData, data, size);
  nullBuffer->isUpdated = 1;
}

void NullBuffer_pop(PortBuffer* _this, int8_t* dst, uint8_t size)
{
  struct NullBuffer_private* nullBuffer = 
    (struct NullBuffer_private*)(_this->privateData);
  if(nullBuffer->size <= size) {
    memcpy(dst, nullBuffer->pData, nullBuffer->size);
  }
  nullBuffer->isUpdated = 0;
}

uint8_t NullBuffer_getNextDataSize(PortBuffer* _this){
  return ((struct NullBuffer_private*)(_this->privateData))->size;
}

uint8_t NullBuffer_hasNext(PortBuffer* _this) {
  return ((struct NullBuffer_private*)(_this->privateData))->isUpdated;
}

