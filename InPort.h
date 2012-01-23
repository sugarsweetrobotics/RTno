#ifndef INPORT_HEADER_INCLUDED
#define INPORT_HEADER_INCLUDED

/*******************************************
 * InPort.h
 * @author Yuki Suga
 * @copyright Yuki Suga (ysuga.net) Nov, 10th, 2010.
 * @license LGPLv3
 *****************************************/

#include "InPortBase.h"
#include "NullBuffer.h"
#include <string.h>
#include <stdlib.h>

class InPortBase : public PortBase{
 private:

 public:
  InPortBase(char* name) {
    pName = (char*)malloc(strlen(name)+1);
    strcpy(pName, name);
    typeCode = 0;
    pPortBuffer = NullBuffer_create();
  }

 public:

};

template<typename T>
class InPort : public InPortBase {
 public:
  T* m_pData;
 public:
 InPort(char* name, T& data) : InPortBase(name) {
    m_pData = &data;
    typeCode = data.typeCode;
  }

  ~InPort() {}
 public:
  int isNew() {
    return pPortBuffer->hasNext(pPortBuffer);
  }

  int read() {
    int dataSize = pPortBuffer->getNextDataSize(pPortBuffer);
    // This code must be okay for little endian system.
    pPortBuffer->pop(pPortBuffer, (char*)&(m_pData->data), dataSize);
    return dataSize;
  }

};



#endif
