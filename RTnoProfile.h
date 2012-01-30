#ifndef RTNO_PROFILE_HEADER_INCLUDED
#define RTNO_PROFILE_HEADER_INCLUDED

#include <stdint.h>
#include "RTno.h"

#include "InPort.h"
#include "OutPort.h"


void RTnoProfile_init();
int RTnoProfile_addInPort(PortBase* port);
int RTnoProfile_addOutPort(PortBase* port);

PortBase* RTnoProfile_getInPort(const char* name, uint8_t nameLen);
PortBase* RTnoProfile_getOutPort(const char* name, uint8_t nameLen);
PortBase* RTnoProfile_getInPortByIndex(const uint8_t i);
PortBase* RTnoProfile_getOutPortByIndex(const uint8_t i);

int RTnoProfile_getNumInPort();
int RTnoProfile_getNumOutPort();

#endif

