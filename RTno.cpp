/*******************************************
 * RTno.cpp
 * @author Yuki Suga
 * @copyright Yuki Suga (ysuga.net) Nov, 10th, 2010.
 * @license LGPLv3
 *****************************************/

#include "RTno.h"
#include "WConstants.h"
#include "HardwareSerial.h"
#include "ReceivePacket.h"
#include "SendPacket.h"

using namespace RTno;

config_str conf;
exec_cxt_str exec_cxt;

enum {
  CREATED='C',
  INACTIVE='I',
  ACTIVE='A',
  ERROR='E',
};

char condition = CREATED;

static char packet_buffer[64];

void setup() {
  rtcconf();
  Serial.begin(conf._default.baudrate);
}


static const char rtc_ok = RTNO_OK;
static const char rtc_error = RTNO_ERROR;
#define LP_RTC_OK (&rtc_ok)
#define LP_RTC_ERROR (&rtc_error)


void loop() {
  ReceivePacket(packet_buffer);

  switch (condition) {
  case CREATED:
    if(packet_buffer[INTERFACE] == INITIALIZE) {
      if(onInitialize() == RTC_OK) {
	condition = INACTIVE;
	SendPacket(INITIALIZE, 1, LP_RTC_OK);
      } else {
	condition = ERROR;
	SendPacket(INITIALIZE, 1, LP_RTC_ERROR);
      }
    }
    break;
  case ERROR:
    if(packet_buffer[INTERFACE] == ONERROR) {
      onError();
      SendPacket(ONERROR, 1, LP_RTC_OK);
    } else if(packet_buffer[INTERFACE] == RESET) {
      if(onReset() == RTC_OK) {
	condition = INACTIVE;
	SendPacket(RESET, 1, LP_RTC_OK);
      } else {
	condition = ERROR;
	SendPacket(RESET, 1, LP_RTC_ERROR);
      }
    }
    break;
  case INACTIVE:
    if(packet_buffer[INTERFACE] == ACTIVATE) {
      if(onActivated() == RTC_OK) {
	condition = ACTIVE;
	SendPacket(ACTIVATE, 1, LP_RTC_OK);
      } else {
	condition = ERROR;
	SendPacket(ACTIVATE, 1, LP_RTC_ERROR);
      }
    }
    break;
  case ACTIVE:
    if(packet_buffer[INTERFACE] == DEACTIVATE) {
      onDeactivated();
      condition = INACTIVE;
      SendPacket(DEACTIVATE, 1, LP_RTC_OK);
    }else if(packet_buffer[INTERFACE] == EXECUTE) {
      if(onExecute() == RTC_OK) {
	SendPacket(EXECUTE, 1, LP_RTC_OK);
      } else {
	condition = ERROR;
	SendPacket(EXECUTE, 1, LP_RTC_ERROR);
      }
    }
    break;
  default:
    condition = ERROR;
    break;
  }

  if(packet_buffer[INTERFACE] == GET_STATUS) {
    SendPacket(GET_STATUS, 1, &condition);
  }
}


/*NNN
l:TimedLong
d:TimedDouble
f:TimedFloat
L:TimedLongSeq
D:TimedDoubleSeq
F:TimedFloatSeq  
*/

void addInPort(InPortBase& Port)
{
  int len = strlen(Port.GetName());
  char *data = (char*)malloc(len+1);
  data[0] = Port.GetTypeCode();
  memcpy(&(data[1]), Port.GetName(), len);
  SendPacket(ADD_INPORT, len+1, data);
  ReceivePacket(packet_buffer);
  free(data);
}

void addOutPort(OutPortBase& Port)
{
  int len = strlen(Port.GetName());
  char *data = (char*)malloc(len+1);
  data[0] = Port.GetTypeCode();
  memcpy(&(data[1]), Port.GetName(), len);
  SendPacket(ADD_OUTPORT, len+1, data);
  ReceivePacket(packet_buffer);
  free(data);
}
