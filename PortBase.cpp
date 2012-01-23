/*******************************************
 * PortBase.h
 * @author Yuki Suga
 * @copyright Yuki Suga (ysuga.net) Nov, 10th, 2010.
 * @license LGPLv3
 *****************************************/
#define RTNO_SUBMODULE_DEFINE

#include <stdlib.h>
#include <string.h>
#include "PortBase.h"
#include "NullBuffer.h"

PortBase* PortBase_create(const char* name, char typeCode, PortBuffer* dataBuffer)
{
  PortBase *portBase = (PortBase*)malloc(sizeof(PortBase));
  portBase->pName = (char*)malloc(strlen(name)+1);
  strcpy(portBase->pName, name);
  portBase->typeCode = typeCode;
  portBase->pPortBuffer = dataBuffer;
  return portBase;
}

void PortBase_destroy(PortBase* pPortBase)
{
  free(pPortBase->pName);
  free(pPortBase);
}

unsigned char PortBase_isSequence(PortBase* pPortBase)
{
  switch(pPortBase->typeCode) {
  case 'b':
  case 'o':
  case 'c':
  case 'l':
  case 'd':
  case 'f':
    return 0;
  default:
    return 1;
  }
}

unsigned char PortBase_getLength(PortBase* pPortBase)
{
  if(!PortBase_isSequence(pPortBase)) {
    return 1;
  } else {
    //    return ((TimedDataSeq*)pPortBase->pData)->GetBuffer()->length();
    return 0;
  }
}

void PortBase_setLength(PortBase* pPortBase, int length)
{
  if(!PortBase_isSequence(pPortBase)) {
    return;
  }
  //  SequenceDataType *seqData = ((TimedDataSeq*)pPortBase->pData)->GetBuffer();
  //  seqData->length(len);
}

#if 0
PortBuffer* PortBase_getBuffer(PortBase* pPortBase) {
  void* pBuffer;
  if(!PortBase_isSequence(pPortBase)) {
    pBuffer = ((TimedData*)(pPortBase->pData))->GetBuffer();
  } else {
    //SequenceDataType *seqData = ((TimedDataSeq*)(pPortBase->pData))->GetBuffer();
    //    pBuffer = seqData->GetBuffer();
  }
  return pBuffer;
}
#endif 

#if 0
void PortBase_push(PortBase* pPortBase, const char* data, int size) {
  pPortBase->pPortBuffer->push(data,size);
}

void PortBase_pop(PortBase* pPortBase, char* data, int size) {
  pPortBase->pPortBuffer->pop(data,size);
}

int PortBase_hasNext(PortBase *pPortBase) {
  return pPortBase->pPortBuffer->hasNext();
}

int PortBase_getNextDataSize(PortBase *pPortBase) {
  return pPortBase->pPortBuffer->getNextDataSize();
}

#endif
