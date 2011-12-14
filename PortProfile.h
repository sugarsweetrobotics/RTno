#ifndef PORT_PROFILE_HEADER_INCLUDED
#define PORT_PROFILE_HEADER_INCLUDED


#include "PortBase.h"

class PortProfile {
public:
	int length;
	char* data;
	
public:
	PortProfile(PortBase &Port);
	virtual ~PortProfile();
};


#endif // #ifndef PORT_PROFILE_HEADER_INCLUDED
