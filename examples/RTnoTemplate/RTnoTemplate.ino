/**
 * RTnoTemplate.ino
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
//#include <SPI.h> 
//#include <Ethernet.h>

/**
 * Include Timer1ExecutionContext.h header
 *  to use Timer1ExecutionContext
 * See Timer1EC example to know in more detail
 */
//#include <Timer1ExecutionContext.h>

/** 
 * Include UART.h header
 *  to use ConnectionTypeSerial1, 2, 3
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
  // conf._default.connection_type = ConnectionTypeSerial2; // This configuration is avaiable in Arduino-Mega
  // conf._default.connection_type = ConnectionTypeSerial3; // This configuration is avaiable in Arduino-Mega
  // conf._default.connection_type = ConnectionTypeEtherTcp; // This configuration is avaiable with Ethernet Shield.
  conf._default.baudrate = 57600;
  exec_cxt.periodic.type = ProxySynchronousExecutionContext;
  
  // Configurations Below are configuration parameter for EtherTcp connection.
  // conf._default.port = 23;
  // conf._default.mac_address = MacAddr(0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED);
  // conf._default.ip_address = IPAddr(192,168,42,100);
  // conf._default.subnet_mask = IPAddr(255,255,255,0);
  // conf._default.default_gateway = IPAddr(192,168,42,254);

  // exec_cxt.periodic.type = Timer1ExecutionContext; // onExecute is called by Timer1. Period must be specified by 'rate' option.
  // *caution: TimerOne can not be used with PWM 9, 10.
  // exec_cxt.periodic.rate = 1000; // [Hz] This option is indispensable when type is Timer*ExecutionContext.
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
//TimedLong in0;
//InPort<TimedLong> in0In("in0", in0);
//TimedLongSeq in1;
//InPort<TimedLongSeq> in1In("in1", in1);

//TimedLong out0;
//OutPort<TimedLong> out0Out("out0", out0);
//TimedLongSeq out1;
//OutPort<TimedLongSeq> out1Out("out1", out1);


//////////////////////////////////////////
// on_initialize
//
// This function is called in the initialization
// sequence when th processor is turned on.
// In on_initialize, usually DataPorts are added.
//
//////////////////////////////////////////
int RTno::onInitialize() {
  /* Data Ports are added in this section.
  addInPort(in0In);
  addInPort(in1In);
  addOutPort(out0Out);
  addOutPort(out1Out);
  */
  
  // Some initialization (like port direction setting)
  // int LED = 13;
  // pinMode(LED, OUTPUT);
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
  if(in0In.isNew()) {
    in0In.read();
    long data = in0.data;
  } 
  */
  
  /**
   * Usage of InPort with sequence type
  if(in1In.isNew(&in1In)) {
    in1In.read();
    for(int i = 0;i < in1.data.length;i++) {
      long data_buffer = in1.data[i];
    }
  }
  */
  
  /**
   * Usage of OutPort with primitive type.
  out0.data = 3.14159;
  out0Out.write();
  */
  
  /**
   * Usage of OutPort with sequence type.
  out1.data.length(3);
  out1.data[0] = 1.1;
  out1.data[1] = 2.2;
  out1.data[2] = 3.3;
  out1Out.write();
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

