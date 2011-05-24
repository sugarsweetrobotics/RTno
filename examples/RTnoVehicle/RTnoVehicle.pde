/**
 * RTnoVehicle.pde
 * RTno is RT-middleware and arduino.
 *
 * This project create Two wheel vehicle robot which is controlled by DirectInput RTC (ysuga.net).
 * 
 *
 * @author Yuki Suga
 * This code is written/distributed for public-domain.
 */

#include <RTno.h>

/**
 * rtcconf()
 *
 * This function is called at first.
 * conf._default.baudrate: baudrate of serial communication
 * exec_cxt.periodic.type: reserved but not used.
 */
void rtcconf(void) {
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
InPort in0In("vel", in0);

/* LED */
#define LED 13

/*
 * Definition of I/O pin
 */
#define RIGHT_IN0 3
#define RIGHT_IN1 5
#define LEFT_IN0  6
#define LEFT_IN1  9

// There must be stop band for stable control
#define STOP_BAND 20

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
  /* Data Ports are added in this section. */
  addInPort(in0In);
  
  // Some initialization (like port direction setting)
  pinMode(LED, OUTPUT);
  
  pinMode(RIGHT_IN0, OUTPUT);
  pinMode(RIGHT_IN1, OUTPUT);
  pinMode(LEFT_IN0, OUTPUT);
  pinMode(LEFT_IN1, OUTPUT);
  
  /** Stop Vehilcle */
  analogWrite(RIGHT_IN0, 0);
  analogWrite(RIGHT_IN1, 0);
  analogWrite(LEFT_IN0,  0);
  analogWrite(LEFT_IN1,  0);
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

  /** Stop Vehilcle */
  analogWrite(RIGHT_IN0, 0);
  analogWrite(RIGHT_IN1, 0);
  analogWrite(LEFT_IN0, 0);
  analogWrite(LEFT_IN1, 0);
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
    digitalWrite(LED, HIGH); // LED on
    in0In.read();

    if(in0.data.length() >= 2) { // if data is avairable
      long forward = -in0.data[1]; // [-1000, +1000]
      long turn    = -in0.data[0]; // [-1000, +1000]
      
      // calculate motor turn velocity
      long right = (forward + turn) / 10; // [-2000, +2000]
      long left  = (forward - turn) / 10; // [-2000, +2000]
      
      // set PWM duty rate 
      if(right > STOP_BAND) {
        analogWrite(RIGHT_IN0, right +25);
        analogWrite(RIGHT_IN1, 0);
      } else if(right < -STOP_BAND) {
        analogWrite(RIGHT_IN1, -right +25);
        analogWrite(RIGHT_IN0, 0);
      } else {
        analogWrite(RIGHT_IN0, 0);
        analogWrite(RIGHT_IN1, 0);
      }

      if(left > STOP_BAND) {
        analogWrite(LEFT_IN0, left +25);
        analogWrite(LEFT_IN1, 0);
      } else if(left < -STOP_BAND) {
        analogWrite(LEFT_IN1, -left +25);
        analogWrite(LEFT_IN0, 0);
      } else {
        analogWrite(LEFT_IN0, 0);
        analogWrite(LEFT_IN1, 0);
      }
      
      digitalWrite(LED, LOW); // LED off
    }
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
  analogWrite(RIGHT_IN0, 0);
  analogWrite(RIGHT_IN1, 0);
  analogWrite(LEFT_IN0, 0);
  analogWrite(LEFT_IN1, 0);
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


