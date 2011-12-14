#ifndef RTNO_PROFILE_HEADER_INCLUDED
#define RTNO_PROFILE_HEADER_INCLUDED

#include "RTno.h"

#include "InPort.h"
#include "OutPort.h"

class RTnoProfile {

private:
	int numInPort;
	InPort *m_ppInPort[MAX_PORT];
	int numOutPort;
	OutPort *m_ppOutPort[MAX_PORT];

public:
	RTnoProfile();
	virtual ~RTnoProfile();

	int addInPort(InPort& port);
	int addOutPort(OutPort& port);
	
	InPort* getInPort(int index) {
	  return m_ppInPort[index];
	}
	OutPort* getOutPort(int index) {
	  return m_ppOutPort[index];
	}
	
	InPort* getInPort(const char* name, int nameLen);
	OutPort* getOutPort(const char* name, int nameLen);

 public:
	int getNumOutPort() {
	  return numOutPort;
	}

	int getNumInPort() {
	  return numInPort;
	}
};


#endif

