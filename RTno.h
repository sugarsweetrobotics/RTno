#ifndef RTNO_HEADER_INCLUDED
#define RTNO_HEADER_INCLUDED

/*******************************************
 * RTno.h
 * @author Yuki Suga
 * @copyright Yuki Suga (ysuga.net) Nov, 10th, 2010.
 * @license LGPLv3
 *****************************************/





#ifdef UART_HEADER_INCLUDED
#define USE_UART_CONNECTION
#endif

#ifdef ethernet_h
#define USE_ETHERNET_CONNECTION
#else
#ifndef USE_UART_CONNECTION // for backward compatibility
#define USE_UART_CONNECTION 
#endif

#endif

#ifdef TIMER1_EXECUTION_CONTEXT
#define USE_TIMER1_EC
#endif

#include <Arduino.h>
#include "Packet.h"
#include "BasicDataType.h"
#include "InPort.h"
#include "OutPort.h"
#include "rtcconf.h"

#ifdef USE_UART_CONNECTION
#include "UART.h"
#endif

#ifdef USE_ETHERNET_CONNECTION
#include "EtherTcp.h"
#endif

#include "ProxySyncEC.h"
#define PACKET_BUFFER_SIZE 128

#define MAX_PORT 8


// Return Code
#define RTC_OK RTNO_RTC_OK
#define RTC_ERROR RTNO_RTC_ERROR

// global variables for rtcconf
//extern volatile exec_cxt_str exec_cxt;
//extern config_str conf;

// global functions
// RTno APIs
extern "C" {
  void rtcconf(config_str& conf, exec_cxt_str& exec_cxt);
};

extern "C" {
  void addInPort(InPortBase& inPort);
  void addOutPort(OutPortBase& outPort);
}

namespace RTno {
  //extern "C" {

  // These call-back funcitons should be defined in user program code.
  // Use RTno_template.pde to create your own project.

  /**
   * onInitialize()
   * This function is called when RTno is initialized.
   * RTno is usually initialized when your device is turned on.
   */
  int onInitialize();

  /**
   * onActivated()
   * This function is called when RTno is activated only if RTno is RTC_INACTIVE condition.
   * RTno is usually activated by RT System Editor or other tools for OpenRTM-aist.
   */
  int onActivated();

  /**
   * onExecute()
   * This function is periodically called when the RTno-proxy is RTC_ACTIVE condition.
   */
  int onExecute();

  /**
   * onDeactivated()
   * This function is called when RTno is deactivated only if RTno is RTC_ACTIVE condition.
   * RTno is usually deactivated by RT System Editor or other tools for OpenRTM-aist.
   */
  int onDeactivated();

  /**
   * onError
   * This function is called when RTno is error only if RTno is in RTC_ERROR condition.
   * [DANGEROUS] This function is periodically called in very short interval.
   */ 
 int onError();

  /**
   * onReset
   * This function is called when RTno is reset only if RTno is in RTC_ERROR condition.
   * RTno is usually reset by RT System Editor or other tools for OpenRTM-aist.
   */
  int onReset();
  //};// extern "C"
};


#ifndef RTNO_SUBMODULE_DEFINE

#ifdef USE_TIMER1_EC

#include <avr/io.h>
#include <avr/interrupt.h>


extern "C" {
  ISR(TIMER1_OVF_vect)
  {
    EC_execute();
  }
}

#endif // USE_TIMER1_EC

void EC_setup(exec_cxt_str& exec_cxt) {
  switch(exec_cxt.periodic.type) {
#ifdef USE_TIMER1_EC
  case Timer1ExecutionContext:
    Timer1EC_init(exec_cxt.periodic.rate);
    break;
#endif // USE_TIMER1_EC
  case ProxySynchronousExecutionContext:
  default:
    ProxySyncEC_init();
    break;
  }
}


void Connection_setup(config_str& conf) {
  switch(conf._default.connection_type) {
#ifdef USE_ETHERNET_CONNECTION
  case ConnectionTypeEtherTcp:
    EtherTcp_init((uint8_t*)&conf._default.mac_address,
		  (uint8_t*)&conf._default.ip_address,
		  (uint8_t*)&conf._default.default_gateway,
		  (uint8_t*)&conf._default.subnet_mask,
    		  conf._default.port);
    break;
#endif // USE_ETHERNET_CONNECTION
#ifdef USE_UART_CONNECTION
  case ConnectionTypeSerial1:
    UART_init(1, conf._default.baudrate);
    break;
  case ConnectionTypeSerial2:
    UART_init(2, conf._default.baudrate);
    break;
  case ConnectionTypeSerial3:
    UART_init(3, conf._default.baudrate);
    break;
#endif // USE_UART_CONNECTION
  default:
    break;
}
}


#endif

#endif

