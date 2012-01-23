#ifndef TRANSPORT_HEADER_INCLUDED
#define TRANSPORT_HEADER_INCLUDED

#include "SerialDevice.h"

int Transport_init();//SerialDevice* pSerialDevice);

int Transport_SendPacket(const char interface, const char data_length, const char* packet_data);
	
int Transport_ReceivePacket(unsigned char* packet);

/*
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
*/
#endif
