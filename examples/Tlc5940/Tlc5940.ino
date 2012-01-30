/**
 * RTnoArm.pde
 * RTno is RT-middleware and arduino.
 *
 * This example depends on the Tlc5940arduino library.
 * http://code.google.com/p/tlc5940arduino/downloads/list
 * This module uses Timer1, so Timer1ExecutionContext can not
 * be used with this.
 *
 * Use PWM shield by sparkfun.com
 * http://www.sparkfun.com/products/10615
 * This shield is properly arranged on the signal pins.
 * 
 * InPort: TimedLongSeq -- max 16 PWM servos' degree (0 to 180)
 *
 * @author Yuki Suga
 * This code is written/distributed for public-domain.
 */

// Never use Timer1ExecutionContext with Tlc5940 library.
#include <UART.h>
#include <RTno.h>
#include <Tlc5940.h>
#include <tlc_servos.h>


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
 * available data types are as follows:
 * TimedLong
 * TimedDouble
 * TimedFloat
 * TimedLongSeq
 * TimedDoubleSeq
 * TimedFloatSeq
 *
 * Please refer following comments. If you need to use some ports,
 * uncomment the line you want to declare.
 **/
TimedLongSeq in0;
InPort<TimedLongSeq> in0In("in0", in0);


//////////////////////////////////////////
// on_initialize
//
// This function is called in the initialization
// sequence when th processor is turned on.
// In on_initialize, usually DataPorts are added.
//
//////////////////////////////////////////
int RTno::onInitialize() {
  /* Data Ports are added in this section. */
  addInPort(in0In);

  tlc_initServos();
  
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

  /**
   * Usage of InPort with premitive type.
   */

  if(in0In.isNew()) {
    in0In.read();
    for(int i = 0; i < in0.data.length() && i < 16;i++) {
      tlc_setServo(i, in0.data[i]); 
    }
    Tlc.update();
  } 

  

    
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

