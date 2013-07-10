#define RTNO_SUBMODULE_DEFINE

#include "Arduino.h"

#include "RTnoProfile.h"

static PortBase *m_ppInPort[MAX_PORT];
static PortBase *m_ppOutPort[MAX_PORT];

void RTnoProfile_init()
{
}

int RTnoProfile_addInPort(PortBase* port) 
{
  int index = RTnoProfile_getNumInPort();
  if(index == MAX_PORT) return -1;
  m_ppInPort[index] = port;
  return index;
}


int RTnoProfile_addOutPort(PortBase* port) 
{
  int index = RTnoProfile_getNumOutPort();
  if(index == MAX_PORT) return -1;
  m_ppOutPort[index] = port;
  return index;
}

int RTnoProfile_getNumInPort() {
  for(int i = 0;i < MAX_PORT;i++) {
    if(m_ppInPort[i] == NULL) {
      return i;
    }
  }
  return MAX_PORT;
}


int RTnoProfile_getNumOutPort() {
  for(int i = 0;i < MAX_PORT;i++) {
    if(m_ppOutPort[i] == NULL) {
      return i;
    }
  }
  return MAX_PORT;

}

PortBase* RTnoProfile_getInPort(const char* name, uint8_t nameLen)
{
  for(uint8_t i = 0;i < MAX_PORT;i++) {
    if(m_ppInPort[i] == NULL) return NULL;
    if(strncmp(name, m_ppInPort[i]->pName, nameLen) == 0) {
      return m_ppInPort[i];
    }
  }
  return NULL;
}


PortBase* RTnoProfile_getOutPort(const char* name, uint8_t nameLen)
{
  for(uint8_t i = 0;i < MAX_PORT;i++) {
    if(m_ppOutPort[i] == NULL) return NULL;
    if(strncmp(name, m_ppOutPort[i]->pName, nameLen) == 0) {
      return m_ppOutPort[i];
    }
  }
  return NULL;
}

PortBase* RTnoProfile_getInPortByIndex(const uint8_t i)
{
  return m_ppInPort[i];
}

PortBase* RTnoProfile_getOutPortByIndex(const uint8_t i)
{
  return m_ppOutPort[i];
}
