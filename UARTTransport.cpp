#include <Arduino.h>
#include "UARTTransport.h"
#include "UART.h"


UARTTransport::UARTTransport(int num, unsigned long baudrate)
{
  m_pSerialDevice = new UART(num, baudrate);
}


UARTTransport::~UARTTransport()
{
  delete m_pSerialDevice;
}
