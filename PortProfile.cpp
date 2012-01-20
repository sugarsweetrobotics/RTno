#define RTNO_SUBMODULE_DEFINE

#include <Arduino.h>
#include "PortProfile.h"



PortProfile::PortProfile(PortBase &Port)
{
  int len = strlen(Port.GetName());
  data = (char*)malloc(len+1);
  length = len+1;
  data[0] = Port.GetTypeCode();
  memcpy(&(data[1]), Port.GetName(), len);
}


PortProfile::~PortProfile()
{
  free(data);
}

