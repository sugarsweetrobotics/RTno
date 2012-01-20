#ifndef RTNO_HEADER_INCLUDED
#define RTNO_HEADER_INCLUDED

/*******************************************
 * RTno.h
 * @author Yuki Suga
 * @copyright Yuki Suga (ysuga.net) Nov, 10th, 2010.
 * @license LGPLv3
 *****************************************/


//#define BAUDRATE 19200

#define RTC_OK 0
#define RTC_ERROR -1
#define RTC_PRECONDITION_NOT_MET -2

#include "BasicDataType.h"
#include "InPort.h"
#include "OutPort.h"
#include "rtcconf.h"

#include "UARTTransport.h"
#ifdef ethernet_h
#include "EtherTCPTransport.h"
#endif

#define PACKET_BUFFER_SIZE 128

#define MAX_PORT 8


// global variables for rtcconf
extern exec_cxt_str exec_cxt;
extern  config_str conf;

// global functions
// RTno APIs
extern "C" {
  void rtcconf(void);
};




extern "C" {
  void addInPort(InPort& inPort);
  void addOutPort(OutPort& outPort);
}

namespace RTno {
extern "C" {
  // setup function is defined in RTno.cpp
  void setup();

  // loop fuction is defined in RTno.cpp
  void loop();


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
  };// extern "C"
};
extern Transport* m_pTransport;

#ifndef RTNO_SUBMODULE_DEFINE
void Connection_setup() {
  switch(conf._default.connection_type) {
  case ConnectionTypeSerial1:
    m_pTransport = new UARTTransport(1, conf._default.baudrate);
    break;
  case ConnectionTypeSerial2:
    m_pTransport = new UARTTransport(2, conf._default.baudrate);
    break;
  case ConnectionTypeSerial3:
    m_pTransport = new UARTTransport(3, conf._default.baudrate);
    break;
#ifdef ethernet_h
  case ConnectionTypeEtherTcp:
    m_pTransport = new EtherTcpTransport(conf._default.mac_address.value,
					 conf._default.ip_address.value,
					 conf._default.default_gateway.value,
					 conf._default.subnet_mask.value,
					 conf._default.port);
#endif
  default:
    return;
  }
}
#endif

#endif

