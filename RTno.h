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



#endif

