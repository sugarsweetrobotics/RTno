#ifndef OUTPORT_HEADER_INCLUDED
#define OUTPORT_HEADER_INCLUDED

/*******************************************
 * OutPort.h
 * @author Yuki Suga
 * @copyright Yuki Suga (ysuga.net) Nov, 10th, 2010.
 * @license LGPLv3
 *****************************************/

#include "PortBase.h"
#include "NullBuffer.h"
#include "TypeCode.h"
#include <string.h>
#include <stdlib.h>

class OutPortBase : public PortBase {
 private:

 public:
  OutPortBase(const char* name) {
    pName = (char*)malloc(strlen(name)+1);
    strcpy(pName, name);
    typeCode = 0;
    pData = NullBuffer_create();
  }

 public:

};

template<typename T>
class OutPort : public OutPortBase {
 private:
  T* m_pData;
  
 public:
 OutPort(const char* name, T& data) : OutPortBase(name) {
    m_pData = &data;
    typeCode = data.typeCode;
  }
  ~OutPort() {}

 public:
  int write() {
    int size = TypeCode_getElementSize(m_pData->typeCode);
    if(TypeCode_isSequence(m_pData->typeCode)) {
      size *= ((SequenceBase)(m_pData->data)).length();
    }
    PortBuffer_push(pPortBuffer, &(m_pData->data), size);
    return size;
  }
};


#endif
