/*******************************************
 * PortBase.h
 * @author Yuki Suga
 * @copyright Yuki Suga (ysuga.net) Nov, 10th, 2010.
 * @license LGPLv3
 *****************************************/

#ifndef PORT_BASE_HEADER_INCLUDED
#define PORT_BASE_HEADER_INCLUDED

#include "BasicDataType.h"
#include "PortBuffer.h"

typedef struct _PortBase {
  unsigned char portBuffer;
  void* pData;
  char* pName;
  char typeCode;
  PortBuffer *pPortBuffer;
} PortBase;

PortBase* PortBase_create(const char* name, char typeCode, void* dataBuffer);
void PortBase_destroy(PortBase* pPortBase);

unsigned char PortBase_isSequence(PortBase* pPortBase);
unsigned char PortBase_getLength(PortBase* pPortBase);
void PortBase_setLength(PortBase* pPortBase, int length);
PortBuffer* PortBase_getBuffer(PortBase* pPortBase);



#endif
