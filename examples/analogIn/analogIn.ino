/**
 * analogIn.ino
 * RTno is RT-middleware and arduino.
 *
 * Using RTno, arduino device can communicate any RT-components 
 *  through the RTno-proxy component which is launched in PC.
 * Connect arduino with USB, and program with RTno library.
 * You do not have to define any protocols to establish communication
 *  between arduino and PC.
 *
 * Using RTno, you must not define the function "setup" and "loop".
 * Those functions are automatically defined in the RTno libarary.
 * You, developers, must define following functions:
 *  int onInitialize(void);
 *  int onActivated(void);
 *  int onDeactivated(void);
 *  int onExecute(void);
 *  int onError(void);
 *  int onReset(void);
 * These functions are spontaneously called by the RTno-proxy
 *  RT-component which is launched in the PC.
 */
#include <UART.h>
#include <RTno.h>

/**
 * This function is called at first.
 * conf._default.baudrate: baudrate of serial communication
 * exec_cxt.periodic.type: reserved but not used.
 */
void rtcconf(config_str& conf, exec_cxt_str& exec_cxt) {
  conf._default.connection_type = ConnectionTypeSerial1;
  conf._default.baudrate = 57600;
  exec_cxt.periodic.type = ProxySynchronousExecutionContext;
}

/** 
 * Declaration Division:
 *
 * DataPort and Data Buffer should be placed here.
 *
 * Currently, following 6 types are available.
 * TimedLong:
 * TimedDouble:
 * TimedFloat:
 * TimedLongSeq:
 * TimedDoubleSeq:
 * TimedFloatSeq:
 *
 * Please refer following comments. If you need to use some ports,
 * uncomment the line you want to declare.
 **/
TimedFloatSeq out0;
OutPort<TimedFloatSeq> out0Out("out0", out0);

//////////////////////////////////////////
// on_initialize
//
// This function is called in the initialization
// sequence. The sequence is triggered by the
// PC. When the RTnoRTC is launched in the PC,
// then, this function is remotely called
// through the USB cable.
// In on_initialize, usually DataPorts are added.
//
//////////////////////////////////////////
int RTno::onInitialize() {
  /* Data Ports are added in this section.
  */
  addOutPort(out0Out);
  
  // Some initialization (like port direction setting)

  return RTC_OK; 
}

////////////////////////////////////////////
// on_activated
// This function is called when the RTnoRTC
// is activated. When the activation, the RTnoRTC
// sends message to call this function remotely.
// If this function is failed (return value 
// is RTC_ERROR), RTno will enter ERROR condition.
////////////////////////////////////////////
int RTno::onActivated() {
  // Write here initialization code.
  
  return RTC_OK; 
}

/////////////////////////////////////////////
// on_deactivated
// This function is called when the RTnoRTC
// is deactivated.
/////////////////////////////////////////////
int RTno::onDeactivated()
{
  // Write here finalization code.

  return RTC_OK;
}

//////////////////////////////////////////////
// This function is repeatedly called when the 
// RTno is in the ACTIVE condition.
// If this function is failed (return value is
// RTC_ERROR), RTno immediately enter into the 
// ERROR condition.r
//////////////////////////////////////////////
int RTno::onExecute() {

  /*
   * Output analog data in Voltage unit.
   */
  out0.data.length(6);
  for(int i = 0;i < 6;i++) {
    out0.data[i] = (analogRead(i) * 5.0f) / 1024;
  }
  out0Out.write();
    
  return RTC_OK; 
}


//////////////////////////////////////
// on_error
// This function is repeatedly called when
// the RTno is in the ERROR condition.
// The ERROR condition can be recovered,
// when the RTno is reset.
///////////////////////////////////////
int RTno::onError()
{
  return RTC_OK;
}

////////////////////////////////////////
// This function is called when 
// the RTno is reset. If on_reset is
// succeeded, the RTno will enter into
// the INACTIVE condition. If failed 
// (return value is RTC_ERROR), RTno
// will stay in ERROR condition.ec
///////////////////////////////////////
int RTno::onReset()
{
  return RTC_OK;
}


