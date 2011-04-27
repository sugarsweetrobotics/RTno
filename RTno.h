#ifndef RTNO_HEADER_INCLUDED
#define RTNO_HEADER_INCLUDED

/*******************************************
 * RTno.h
 * @author Yuki Suga
 * @copyright Yuki Suga (ysuga.net) Nov, 10th, 2010.
 * @license LGPLv3
 *****************************************/


#define BAUDRATE 19200

#define RTC_OK 0
#define RTC_ERROR -1

#include "BasicDataType.h"
#include "InPort.h"
#include "OutPort.h"

struct config_str {
#ifndef RTNO_HEADER_INCLUDED
#define RTNO_HEADER_INCLUDED

/*******************************************
 * RTno.h
 * @author Yuki Suga
 * @copyright Yuki Suga (ysuga.net) Nov, 10th, 2010.
 * @license LGPLv3
 *****************************************/


#define BAUDRATE 19200

#define RTC_OK 0
#define RTC_ERROR -1

#include "BasicDataType.h"
#include "InPort.h"
#include "OutPort.h"



struct config_str {
	struct default_str {
		int baudrate;
	}_default;
};

struct exec_cxt_str {
	struct periodic_str {
		int type;
	}periodic;
};

#define ProxySynchronousExecutionContext 1

extern exec_cxt_str exec_cxt;

extern  config_str conf;


extern "C" {
  void rtcconf(void);
};

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
   * RTno is usually initialized when the RTno-proxy is launched.
   */
  int onInitialize();

  /**
   * onActivated()
   * This function is called when RTno is activated.
   * RTno is usually activated by RT System Editor or other tools for OpenRTM-aist.
   */
  int onActivated();

  /**
   * onExecute()
   * This function is periodically called when the RTno-proxy is active.
   */
  int onExecute();

  /**
   * onDeactivated()
   * This function is called when RTno is deactivated.
   * RTno is usually deactivated by RT System Editor or other tools for OpenRTM-aist.
   */
  int onDeactivated();

  /**
   * onError
   * This function is called when RTno is error.
   * [DANGEROUS] This function is periodically called in very short interval.
   */
  int onError();

  /**
   * onReset
   * This function is called when RTno is reset.
   * RTno is usually reset by RT System Editor or other tools for OpenRTM-aist.
   */
  int onReset();

};



#endif
}

extern "C" {
void addInPort(InPortBase& inPort);
void addOutPort(OutPortBase& outPort);
}
  struct default_str {
    int baudrate;
  }default;
};

extern  config_str conf;


extern "C" {
  void rtcconf(void);
};

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
   * RTno is usually initialized when the RTno-proxy is launched.
   */
  int onInitialize();

  /**
   * onActivated()
   * This function is called when RTno is activated.
   * RTno is usually activated by RT System Editor or other tools for OpenRTM-aist.
   */
  int onActivated();

  /**
   * onExecute()
   * This function is periodically called when the RTno-proxy is active.
   */
  int onExecute();

  /**
   * onDeactivated()
   * This function is called when RTno is deactivated.
   * RTno is usually deactivated by RT System Editor or other tools for OpenRTM-aist.
   */
  int onDeactivated();

  /**
   * onError
   * This function is called when RTno is error.
   * [DANGEROUS] This function is periodically called in very short interval.
   */
  int onError();

  /**
   * onReset
   * This function is called when RTno is reset.
   * RTno is usually reset by RT System Editor or other tools for OpenRTM-aist.
   */
  int onReset();

};



#endif
}

extern "C" {
void addInPort(InPortBase& inPort);
void addOutPort(OutPortBase& outPort);
}
