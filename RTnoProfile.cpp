#define RTNO_SUBMODULE_DEFINE

#include <Arduino.h>

#include "RTnoProfile.h"

RTnoProfile::RTnoProfile()
{
	numInPort = 0;
	numOutPort = 0;
	for(int i = 0;i < MAX_PORT;i++) {
		m_ppInPort[i] = NULL;
		m_ppOutPort[i] = NULL;
	}
}


RTnoProfile::~RTnoProfile()
{
//	for(int i = 0;i < MAX_PORT;i++) {
//		delete m_ppInPortProfile[i];
//		delete m_ppOutPortProfile[i];
//	}
}


int RTnoProfile::addInPort(InPort& port) 
{
	if(numInPort == 8) return -1;

	m_ppInPort[numInPort] = &port;	
	numInPort++;
	return numInPort;
}


int RTnoProfile::addOutPort(OutPort& port) 
{
	if(numOutPort == 8) return -1;
	
	m_ppOutPort[numOutPort] = &port;
	numOutPort++;
	return numOutPort;
}

InPort* RTnoProfile::getInPort(const char* name, int nameLen)
{
	for(int i = 0;i < numInPort;i++) {
		if(strncmp(name, m_ppInPort[i]->GetName(), nameLen) == 0) {
			return m_ppInPort[i];
		}
	}
	return NULL;
}


OutPort* RTnoProfile::getOutPort(const char* name, int nameLen)
{
	for(int i = 0;i < numOutPort;i++) {
		if(strncmp(name, m_ppOutPort[i]->GetName(), nameLen) == 0) {
			return m_ppOutPort[i];
		}
	}
	return NULL;
}
