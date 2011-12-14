#ifndef UART_TRANSPORT_HEADER_INCLUDED
#define UART_TRANSPORT_HEADER_INCLUDED


#include "Transport.h"

class UARTTransport : public Transport {
	
private:


public:
	UARTTransport(int num, unsigned long baudrate);
	
	~UARTTransport();
};

#endif // #ifndef UART_TRANSPORT_HEADER_INCLUDED
