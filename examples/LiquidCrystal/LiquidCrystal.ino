/**
 * LiquidCrystal.ino
 * RTno is RT-middleware and arduino.
 * 
 * This example uses LiquidCrystal library.
 * http://arduino.cc/en/Reference/LiquidCrystalConstructor
 *
 * This program is tested by LCD shield by Prototyping Lab.
 * http://prototypinglab.com
 *
 * @author Yuki Suga
 * This code is written/distributed for public-domain.
 */
#include <UART.h>
#include <RTno.h>
#include <LiquidCrystal.h>

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
TimedLong in0;
InPort<TimedLong> in0In("in0", in0);


// Initialize the library with the numbers of the interface pins.
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

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
 
  lcd.begin(16, 2);
  
  lcd.setCursor(0, 0);
  lcd.print("RTC_INACTIVE  ");
   
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
  
  lcd.setCursor(0, 0);
  lcd.print("RTC_ACTIVE   ");
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
  lcd.setCursor(0, 0);
  lcd.print("RTC_INACTIVE   ");
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
    long data = in0.data;
    lcd.setCursor(0, 1);
    lcd.print("data=           ");
    lcd.setCursor(6,1);
    lcd.print(data, DEC);
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

