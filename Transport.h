#ifndef TRANSPORT_HEADER_INCLUDED
#define TRANSPORT_HEADER_INCLUDED

#include "SerialDevice.h"

class Transport {
	
private:


protected:
	SerialDevice *m_pSerialDevice;
	
public:
	Transport() {}
	virtual ~Transport() {}
	
	int SendPacket(const char interface, const char data_length, const char* packet_data);
	
	int ReceivePacket(unsigned char* packet);
	
};

#endif
