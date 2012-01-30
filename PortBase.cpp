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

PortBase* PortBase_create() {
  return (PortBase*)malloc(sizeof(PortBase));
}

void PortBase_init(PortBase* portBase, const char* name, char typeCode, PortBuffer* dataBuffer)
{
  portBase->pName = (char*)malloc(strlen(name)+1);
  strcpy(portBase->pName, name);
  portBase->typeCode = typeCode;
  portBase->pPortBuffer = dataBuffer;
}

void PortBase_destroy(PortBase* pPortBase)
{
  free(pPortBase->pName);
  free(pPortBase);
}
