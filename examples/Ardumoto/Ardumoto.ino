/**
 * RTnoVehicle.pde
 * RTno is RT-middleware and arduino.
 *
 * 
 * 
 *
 * @author Yuki Suga
 * This code is written/distributed for public-domain.
 */

#include <UART.h>
#include <RTno.h>

/**
 * rtcconf()
 *
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
 * TimedBoolean
 * TimedChar
 * TimedOctet
 * TimedLong
 * TimedDouble
 * TimedFloat
 * TimedBooleanSeq
 * TimedCharSeq
 * TimedOctetSeq
 * TimedLongSeq
 * TimedDoubleSeq
 * TimedFloatSeq
 *
 * Please refer following comments. If you need to use some ports,
 * uncomment the line you want to declare.
 **/
TimedLongSeq in0;
InPort<TimedLongSeq> in0In("vel", in0);

/*
 * Definition of I/O pin
 */

static const int pinMotorADir = 12;
static const int pinMotorAPWM = 3;
static const int pinMotorBDir = 13;
static const int pinMotorBPWM = 11;

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
  
  // Some initialization (like port direction setting)
  pinMode(pinMotorADir, OUTPUT);
  pinMode(pinMotorBDir, OUTPUT);
  pinMode(pinMotorAPWM, OUTPUT);
  pinMode(pinMotorBPWM, OUTPUT);

  digitalWrite(pinMotorADir, LOW);  
  digitalWrite(pinMotorBDir, LOW);  
  analogWrite(pinMotorAPWM, 0);
  analogWrite(pinMotorBPWM, 0);
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
  
  digitalWrite(pinMotorADir, LOW);  
  digitalWrite(pinMotorBDir, LOW);  
  analogWrite(pinMotorAPWM, 0);
  analogWrite(pinMotorBPWM, 0);

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

  digitalWrite(pinMotorADir, LOW);  
  digitalWrite(pinMotorBDir, LOW);  
  analogWrite(pinMotorAPWM, 0);
  analogWrite(pinMotorBPWM, 0);
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

  /* Read Input Port */
  if(in0In.isNew()) {
    in0In.read();
    long vel_a = in0.data[0];
    long vel_b = in0.data[1];
    if(vel_a < 0) {
      digitalWrite(pinMotorADir, HIGH);
      vel_a = -vel_a;
    }else {
      digitalWrite(pinMotorADir, LOW);
    }
    if(vel_b < 0) {
      digitalWrite(pinMotorBDir, HIGH);
      vel_b = -vel_b;
    } else {
      digitalWrite(pinMotorBDir, LOW);
    }
    if(vel_a > 255) vel_a = 255;
    if(vel_b > 255) vel_b = 255;
    analogWrite(pinMotorAPWM, vel_a);
    analogWrite(pinMotorBPWM, vel_b);
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
  /** Stop Vehilcle */
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


