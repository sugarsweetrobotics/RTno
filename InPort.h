#ifndef INPORT_HEADER_INCLUDED
#define INPORT_HEADER_INCLUDED

/*******************************************
 * InPort.h
 * @author Yuki Suga
 * @copyright Yuki Suga (ysuga.net) Nov, 10th, 2010.
 * @license LGPLv3
 *****************************************/

#include <stdint.h>
#include "PortBase.h"
#include "NullBuffer.h"
#include <string.h>
#include <stdlib.h>

class InPortBase : public PortBase{
 private:

 public:
  InPortBase(char* name, char tCode) {
    PortBase_init(this, name, tCode, NullBuffer_create());
  }

 public:

};

template<typename T>
class InPort : public InPortBase {
 public:
  T* m_pData;
 public:
 InPort(char* name, T& data) : InPortBase(name, data.typeCode) {
    m_pData = &data;
  }

  ~InPort() {}
 public:
  uint8_t isNew() {
    return pPortBuffer->hasNext(pPortBuffer);
  }

  uint8_t read() {
    uint8_t dataSize = pPortBuffer->getNextDataSize(pPortBuffer);
    if(TypeCode_isSequence(m_pData->typeCode)) {
      ((SequenceBase*)&(m_pData->data))->length(dataSize/TypeCode_getElementSize(m_pData->typeCode));
      pPortBuffer->pop(pPortBuffer, (int8_t*)((SequenceBase*)&(m_pData->data))->getData(), dataSize);
    } else {
    // This code must be okay for little endian system.
      pPortBuffer->pop(pPortBuffer, (int8_t*)&(m_pData->data), dataSize);
    }
    return dataSize;
  }

};



#endif
