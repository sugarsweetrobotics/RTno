/*******************************************
 * RTno.cpp
 * @author Yuki Suga
 * @copyright Yuki Suga (ysuga.net) Nov, 10th, 2010.
 * @license LGPLv3
 *****************************************/
#define RTNO_SUBMODULE_DEFINE
#include <stdint.h>
#include <Arduino.h>

#include "RTno.h"
#include "Packet.h"

#include "Connection.h"
#include "Transport.h"
//#include "UART.h"
#include "RTnoProfile.h"

using namespace RTno;

// global variables
// module private variables.
#define PRIVATE static

// static value declaration.
void(*SerialDevice_init)(const char* address);

void(*SerialDevice_putc)(const char c);
uint8_t(*SerialDevice_available)();
char(*SerialDevice_getc)();
void(*SerialDevice_setTarget)(const char* address);
uint8_t(*SerialDevice_read)(int8_t* dst, const uint8_t maxSize);
void(*SerialDevice_write)(const int8_t* src, const uint8_t size);


PRIVATE char m_pFromInfo[4];
PRIVATE int8_t m_pPacketBuffer[PACKET_BUFFER_SIZE];

/*
 * Send Profile Data
 */
PRIVATE void _SendProfile();
PRIVATE void _SendOutPortData(PortBase* pOutPort);
PRIVATE void _ReceiveInPortData(); 

void EC_setup(exec_cxt_str& exec_cxt);
void Connection_setup(config_str& conf);

/**
 * Arduino Setup Routine.
 * This function is called when arduino device is turned on.
 */
void setup() {
  RTnoProfile_init();
  // This function must be called first.
  exec_cxt_str* exec_cxt = (exec_cxt_str*)malloc(sizeof(exec_cxt_str));
  config_str* conf = (config_str*)malloc(sizeof(config_str));
  rtcconf(*conf, *exec_cxt);
  if(onInitialize() == RTC_OK) {
    EC_setup(*exec_cxt);
    Connection_setup(*conf);
    Transport_init();
    free(exec_cxt);
    free(conf);
    EC_start();
  }
}


/**
 * Arduino Loop routine.
 * This function is repeadedly called when arduino is turned on.
 */
void loop() {
  int8_t ret;
  ret = Transport_ReceivePacket(m_pPacketBuffer, m_pFromInfo);
  if(ret < 0) { // Timeout Error or Checksum Error
    Transport_SendPacket(PACKET_ERROR, 1, &ret);
  } else if (ret == 0) {
    
  } else if (ret > 0) { // Packet is successfully received
    int8_t state = EC_get_component_state();
    int8_t type = EC_get_type();
    int8_t retval = RTNO_OK;
    switch(m_pPacketBuffer[INTERFACE]) {
    case GET_PROFILE:
      _SendProfile();
      break;
    case GET_STATUS:
      Transport_SendPacket(GET_STATUS, 1, &state);
      break;
    case GET_CONTEXT:
      Transport_SendPacket(GET_CONTEXT, 1, &type);
      break;
    case DEACTIVATE:
      ret = EC_deactivate_component();
      if(ret < 0) retval = RTNO_ERROR;
      Transport_SendPacket(DEACTIVATE, 1, &retval);
      break;
    case ACTIVATE:
      ret = EC_activate_component();
      if(ret < 0) retval = RTNO_ERROR;
      Transport_SendPacket(ACTIVATE, 1, &retval);
      break;
    case EXECUTE:
      if(state == RTC_STATE_ACTIVE) {
	ret = EC_execute();
      } else if (state == RTC_STATE_ERROR) {
	ret = EC_error();
      }
      if(ret < 0) retval = RTNO_ERROR;
      Transport_SendPacket(EXECUTE, 1, &retval);
      break;
    case RESET:
      ret = EC_reset_component();
      if(ret < 0) retval = RTNO_ERROR;
      Transport_SendPacket(RESET, 1, &retval);
      break;
    case SEND_DATA:
      if(Connection_isConnected(m_pFromInfo)) {
	_ReceiveInPortData();
      }
      break;

    default:
      break;
    }// switch
  }
  
  int numOutPort = RTnoProfile_getNumOutPort();
  for(int i = 0;i < numOutPort;i++) {
    EC_suspend();
    PortBase* pOutPort = RTnoProfile_getOutPortByIndex(i);
    if(pOutPort->pPortBuffer->hasNext(pOutPort->pPortBuffer)) {
      _SendOutPortData(pOutPort); 
    }
    EC_resume();
  }
  
}




/**
 * add InPort data to Profile.
 */
void addInPort(InPortBase& Port)
{
  RTnoProfile_addInPort(&Port);
}

/**
 * add OutPort data to Profile
 */
void addOutPort(OutPortBase& Port)
{
  RTnoProfile_addOutPort(&Port);
}


/**
 * Private Function Definitions
 *
 */


/**
 * Send Profile Data
 */
PRIVATE void _SendProfile() {
  int8_t ret = RTNO_OK;
  for(uint8_t i = 0;i < RTnoProfile_getNumInPort();i++) {
    PortBase* inPort = RTnoProfile_getInPortByIndex(i);
    uint8_t nameLen = strlen(inPort->pName);
    m_pPacketBuffer[0] = inPort->typeCode;
    memcpy(&(m_pPacketBuffer[1]), inPort->pName, nameLen);
    Transport_SendPacket(ADD_INPORT, 1+nameLen, m_pPacketBuffer);
  }

  for(uint8_t i = 0;i < RTnoProfile_getNumOutPort();i++) {
    PortBase* outPort = RTnoProfile_getOutPortByIndex(i);
    uint8_t nameLen = strlen(outPort->pName);
    m_pPacketBuffer[0] = outPort->typeCode;
    memcpy(&(m_pPacketBuffer[1]), outPort->pName, nameLen);
    Transport_SendPacket(ADD_OUTPORT, 1+nameLen, m_pPacketBuffer);
  }

  Transport_SendPacket(GET_PROFILE, 1, &ret);
}


void _SendOutPortData(PortBase* pOutPort)
{
  char *name = pOutPort->pName;
  uint8_t dataLen = pOutPort->pPortBuffer->getNextDataSize(pOutPort->pPortBuffer);
  if(pOutPort == NULL) return;
  uint8_t nameLen = strlen(name);
  m_pPacketBuffer[0] = nameLen;
  m_pPacketBuffer[1] = dataLen;
  memcpy(m_pPacketBuffer + 2, name, nameLen);
  pOutPort->pPortBuffer->pop(pOutPort->pPortBuffer, m_pPacketBuffer + 2 + nameLen, dataLen);
  ConnectionIterator_init(pOutPort);
  while(ConnectionIterator_hasNext()) {
    ConnectionIterator_next();
    Transport_SendPacket(RECEIVE_DATA, 2 + nameLen + dataLen, m_pPacketBuffer);
  }
}

void _ReceiveInPortData() {
  int8_t ret = RTNO_OK;
  PortBase* pInPort = RTnoProfile_getInPort((const char*)&(m_pPacketBuffer[DATA_START_ADDR+2]), m_pPacketBuffer[DATA_START_ADDR]);
  if(pInPort != NULL) {
    EC_suspend();
    pInPort->pPortBuffer->push(pInPort->pPortBuffer,&(m_pPacketBuffer[DATA_START_ADDR+2+m_pPacketBuffer[DATA_START_ADDR]]), m_pPacketBuffer[DATA_START_ADDR+1]);
    Transport_SendPacket(SEND_DATA, 1, &ret);
    EC_resume();
  }
}





