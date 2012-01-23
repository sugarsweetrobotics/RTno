#define RTNO_SUBMODULE_DEFINE

#include <Arduino.h>
#include "PortProfile.h"


PortProfile* PortProfile_create(const char* name, const char typeCode)
{
  PortProfile* pProf = (PortProfile*)malloc(sizeof(PortProfile));
  int len = strlen(name);
  pProf->data = (char*)malloc(len+1);
  pProf->length = len+1;
  pProf->data[0] = typeCode;
  memcpy(&(pProf->data[1]), name, len);
  return pProf;
}


void PortProfile_destroy(PortProfile* pProfile) {
  free(pProfile->data);
  free(pProfile);
}


/*
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

*/
