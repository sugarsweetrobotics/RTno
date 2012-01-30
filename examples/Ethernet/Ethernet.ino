/**
 * Ethernet.ino
 * RTno is RT-middleware and arduino.
 *
 * This example works with Ethernet Shield by arduino.cc
 * Ethernet Shield uses SPI module and SD card which is
 * on digital pins 4, 10, 11, 12, and 13 on the UNO, and
 * on digital pins 50, 51, 52, and 53 on the Mega.
 * see
 * http://arduino.cc/en/Main/ArduinoEthernetShield
 *
 * !!CAUTION!!
 * Specify your Ethernet Shield's version.
 * In case you use old version, your shield is not
 * available to use with arduino MEGA.
 *
 * Use serial connecction with the UNO to debug the
 * input/output using Serila Monitor on arduino IDE.
 * @author Yuki Suga
 * This code is written/distributed for public-domain.
 */


/**
 * Include "SPI.h" and "Ethernet.h" headers 
 *  to use Ethernet module.
 * If you do not need to use ethernet module,
 *  do not include them, which make the compiled
 *　 binary much smaller.
 */
#include <SPI.h> 
#include <Ethernet.h>
#include <Timer1ExecutionContext.h>
#include <RTno.h>


/**
 * This function is called at first.
 * conf._default
 .baudrate: baudrate of serial communication
 * exec_cxt.periodic.type: reserved but not used.
 */
void rtcconf(config_str& conf, exec_cxt_str& exec_cxt) {
  conf._default.connection_type = ConnectionTypeEtherTcp;
  
  conf._default.port = 23;
  conf._default.mac_address = MACaddr(0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED);
  conf._default.ip_address = IPaddr(192,168,42,100);
  conf._default.subnet_mask = IPaddr(255,255,255,0);
  conf._default.default_gateway = IPaddr(192,168,42,254);

  exec_cxt.periodic.type = Timer1ExecutionContext;
  exec_cxt.periodic.rate = 100;
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
TimedLong in0;
InPort<TimedLong> in0In("in0", in0);


TimedLong out0;
OutPort<TimedLong> out0Out("out0", out0);


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
  /* Data Ports are added in this section.*/
  addInPort(in0In);
  addOutPort(out0Out);
  
  Serial.begin(9600);
  Serial.println("onInitialized!!");
  Serial.flush();
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
  Serial.println("onActivated!!");
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
  Serial.println("onDeactivated!!");
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

  if(in0In.isNew()) {
    in0In.read();
    long data = in0.data;
    Serial.print("ReceivedData = "); Serial.println(data, DEC);
  } 

  static long count;
  count++;
  if((count % 100) == 0) {
    out0.data = count;
    out0Out.write();
    Serial.print("SentData = "); Serial.println(count, DEC);
  }
  /**
   * Usage of OutPort with primitive type.
  out0.data = 3.14159;
  out0Out.write();
  */
  
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

