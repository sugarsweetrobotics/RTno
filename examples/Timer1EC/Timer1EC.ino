/**
 * Timer1EC.pde
 * RTno is RT-middleware and arduino.
 *
 * This sample program uses Timer1ExecutionContext.
 * Timer1ExecutionContext is an ExecutionContext which
 * calls onExecute function periodically when the RTno
 * is in ACTIVE state.
 *
 * Timer1ExecutionContext uses TimerOne module to make 
 * the periodic interruption so the period is comparably 
 * accurate, but the PWM 9, 10 can not be used when TimerOne
 * is used.
 *
 * TimerOne module is originally developed by 
 * http://code.google.com/p/arduino-timerone/
 *
 * This sample program just flash the LED (13th pin)
 * when RTno is activated.
 *
 * Change the exec_cxt.periodic.rate option and confirm 
 * the flashing period changes.
 *
 * @author Yuki Suga
 * This code is written/distributed for public-domain.
 */

// If you want to use Timer1 Execution Context
// First, include this header.
// Second, configure exec_cxt.periodic.type = Timer1EexecutionContext
// Third, configure exec_cxt.periodic.rate = *** [Hz]
#include <Timer1ExecutionContext.h> 
#include <UART.h>
#include <RTno.h>

/**
 * This function is called at first.
 * conf._default.baudrate: baudrate of serial communication
 * exec_cxt.periodic.type: Timer1
 */
void rtcconf(config_str& conf, exec_cxt_str& exec_cxt) {
  conf._default.baudrate = 57600;
  conf._default.connection_type = ConnectionTypeSerial1;
  exec_cxt.periodic.type = Timer1ExecutionContext;
  exec_cxt.periodic.rate = 10; // [Hz]
}


// No InPort and OutPort.

int LED = 13;

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
  // LED pin Initialization
  pinMode(LED, OUTPUT);
  digitalWrite(LED, LOW);
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

  static int i;
  i++;
  if(i == 10) {
    digitalWrite(LED, HIGH);
  } else if(i == 20) {
    digitalWrite(LED, LOW);
    i = 0;
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


