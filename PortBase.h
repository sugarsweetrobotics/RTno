/*******************************************
 * PortBase.h
 * @author Yuki Suga
 * @copyright Yuki Suga (ysuga.net) Nov, 10th, 2010.
 * @license LGPLv3
 *****************************************/

#ifndef PORT_BASE_HEADER_INCLUDED
#define PORT_BASE_HEADER_INCLUDED

#include <stdint.h>
#include "BasicDataType.h"
#include "PortBuffer.h"

typedef struct _PortBase {
  unsigned char portBuffer;
  void* pData;
  char* pName;
  char typeCode;
  PortBuffer *pPortBuffer;
} PortBase;

PortBase* PortBase_create();
void PortBase_init(PortBase* pPortBase, const char* name, char typeCode, PortBuffer* dataBuffer);
void PortBase_destroy(PortBase* pPortBase);

uint8_t PortBase_isSequence(PortBase* pPortBase);
uint8_t PortBase_getLength(PortBase* pPortBase);
void PortBase_setLength(PortBase* pPortBase, uint8_t length);
PortBuffer* PortBase_getBuffer(PortBase* pPortBase);



#endif
