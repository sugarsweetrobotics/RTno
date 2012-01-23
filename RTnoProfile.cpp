#define RTNO_SUBMODULE_DEFINE

#include <Arduino.h>

#include "RTnoProfile.h"

static int numInPort = 0;
static int numOutPort = 0;
static PortBase *m_ppInPort[MAX_PORT];
static PortBase *m_ppOutPort[MAX_PORT];

void RTnoProfile_init()
{
}

int RTnoProfile_addInPort(PortBase* port) 
{
  if(numInPort == 8) return -1;
  m_ppInPort[numInPort] = port;	
  numInPort++;
  return numInPort;
}


int RTnoProfile_addOutPort(PortBase* port) 
{
  if(numOutPort == 8) return -1;
  m_ppOutPort[numOutPort] = port;
  numOutPort++;
  return numOutPort;
}

int RTnoProfile_getNumInPort() {
  return numInPort;
}


int RTnoProfile_getNumOutPort() {
  return numOutPort;
}

PortBase* RTnoProfile_getInPort(const char* name, int nameLen)
{
  for(int i = 0;i < numInPort;i++) {
    if(strncmp(name, m_ppInPort[i]->pName, nameLen) == 0) {
      return m_ppInPort[i];
    }
  }
  return NULL;
}


PortBase* RTnoProfile_getOutPort(const char* name, int nameLen)
{
  for(int i = 0;i < numOutPort;i++) {
    if(strncmp(name, m_ppOutPort[i]->pName, nameLen) == 0) {
      return m_ppOutPort[i];
    }
  }
  return NULL;
}

PortBase* RTnoProfile_getInPortByIndex(const int i)
{
  return m_ppInPort[i];
}

PortBase* RTnoProfile_getOutPortByIndex(const int i)
{
  return m_ppOutPort[i];
}
