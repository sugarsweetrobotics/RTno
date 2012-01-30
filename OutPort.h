#ifndef OUTPORT_HEADER_INCLUDED
#define OUTPORT_HEADER_INCLUDED

/*******************************************
 * OutPort.h
 * @author Yuki Suga
 * @copyright Yuki Suga (ysuga.net) Nov, 10th, 2010.
 * @license LGPLv3
 *****************************************/

#include <stdint.h>
#include "PortBase.h"
#include "PortBuffer.h"
#include "NullBuffer.h"
#include "TypeCode.h"
#include <string.h>
#include <stdlib.h>

class OutPortBase : public PortBase {
 private:

 public:
  OutPortBase(const char* name, char tCode) {
    PortBase_init(this, name, tCode, NullBuffer_create());
  }

 public:

};

template<typename T>
class OutPort : public OutPortBase {
 private:
  T* m_pData;
  
 public:
 OutPort(const char* name, T& data) : OutPortBase(name, data.typeCode) {
    m_pData = &data;
  }
  ~OutPort() {}

 public:
  uint8_t write() {
    uint8_t size = TypeCode_getElementSize(m_pData->typeCode);
    if(TypeCode_isSequence(m_pData->typeCode)) {
      size *= ((SequenceBase*)&(m_pData->data))->length();
      pPortBuffer->push(pPortBuffer,
			(int8_t*)((SequenceBase*)&(m_pData->data))->getData(),
			size);
    } else {
      pPortBuffer->push(pPortBuffer, (const int8_t*)&(m_pData->data), size);
    }
    return size;
  }
};


#endif
