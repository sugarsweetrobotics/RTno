/*******************************************
 * RTno.cpp
 * @author Yuki Suga
 * @copyright Yuki Suga (ysuga.net) Nov, 10th, 2010.
 * @license LGPLv3
 *****************************************/
#define RTNO_SUBMODULE_DEFINE
#include <stdint.h>
#include "Arduino.h"

#include "RTno.h"
#include "Packet.h"

#include "Transport.h"
//#include "UART.h"
#include "RTnoProfile.h"

using namespace RTno;

// global variables
// module private variables.
#define PRIVATE static


PRIVATE int8_t m_pPacketBuffer[PACKET_BUFFER_SIZE];

/*
 * Send Profile Data
 */
PRIVATE void _SendProfile();

/**
 * Packet Handler in Error State.
 */
PRIVATE void _PacketHandlerOnError();

/**
 * Packet Handler in Inactive State.
 */
PRIVATE void _PacketHandlerOnInactive();

/**
 * Packet Handler in Active State.
 */
PRIVATE void _PacketHandlerOnActive();

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
    free(exec_cxt);
    free(conf);
    Transport_init();
    EC_start();
  }
}

/**
 * Arduino Loop routine.
 * This function is repeadedly called when arduino is turned on.
 */
void loop() {
  int8_t ret;
  uint32_t timeout = 20*1000;
  ret = Transport_ReceivePacket((uint8_t*)m_pPacketBuffer, timeout);
  if(ret < 0) { // Timeout Error or Checksum Error
    if(ret == -CHECKSUM_ERROR) {
		 Transport_SendPacket(PACKET_ERROR_CHECKSUM, 1, (int8_t*)&ret);
	} else if(ret == -TIMEOUT) {
		 Transport_SendPacket(PACKET_ERROR_TIMEOUT, 1, (int8_t*)&ret);
	}else {
    	Transport_SendPacket(PACKET_ERROR, 1, (int8_t*)&ret);
    }
  } else if (ret == 0) {

  } else if (ret > 0) { // Packet is successfully received
    if (m_pPacketBuffer[INTERFACE] == GET_PROFILE) {
      _SendProfile();
    } else if(m_pPacketBuffer[INTERFACE] == GET_STATUS) {
      int8_t state = EC_get_component_state();
      Transport_SendPacket(GET_STATUS, 1, &state);
    } else if(m_pPacketBuffer[INTERFACE] == GET_CONTEXT) {
      int8_t type = EC_get_type();
      Transport_SendPacket(GET_CONTEXT, 1, &type);
    } else {
      switch(EC_get_component_state()) {
      case RTC_STATE_ERROR:
        _PacketHandlerOnError();
        break;
      case RTC_STATE_INACTIVE:
        _PacketHandlerOnInactive();
        break;
      case RTC_STATE_ACTIVE:
        _PacketHandlerOnActive();
        break;
      case RTC_STATE_NONE:
        ret = RTNO_NONE;
        Transport_SendPacket(m_pPacketBuffer[INTERFACE], 1, (int8_t*)&ret);
    break;
      default: // if m_Condition is unknown...
    
    break;
      }
    }
  }

  
  int numOutPort = RTnoProfile_getNumOutPort();
  for(int i = 0;i < numOutPort;i++) {
    EC_suspend();
    PortBase* pOutPort = RTnoProfile_getOutPortByIndex(i);
    if(pOutPort->pPortBuffer->hasNext(pOutPort->pPortBuffer)) {
      char* name = pOutPort->pName;
      unsigned char nameLen = strlen(name);
      unsigned char dataLen = pOutPort->pPortBuffer->getNextDataSize(pOutPort->pPortBuffer);

      m_pPacketBuffer[0] = nameLen;
      m_pPacketBuffer[1] = dataLen;
      memcpy(m_pPacketBuffer + 2, name, nameLen);
      pOutPort->pPortBuffer->pop(pOutPort->pPortBuffer, m_pPacketBuffer + 2 + nameLen, dataLen);
      Transport_SendPacket(RECEIVE_DATA, 2 + nameLen + dataLen, m_pPacketBuffer);
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



/**
 * Packet Handler in Error State
 */
PRIVATE void _PacketHandlerOnError() {
  char intface;
  int8_t ret = RTNO_OK;

  int8_t retval = EC_error();
  if(retval < 0) ret = RTNO_ERROR;
  Transport_SendPacket(intface, 1, &ret);
}


/** 
 * Packet Handler in Inactive State
 */
PRIVATE void _PacketHandlerOnInactive() {

  int8_t ret = RTNO_OK;
  int8_t retval = EC_activate_component();
  if(retval < 0) ret = RTNO_ERROR;
  Transport_SendPacket(ACTIVATE, 1, &ret);
}

/**
 * Packet Handler in Active State.
 */
PRIVATE void _PacketHandlerOnActive() {
  int8_t ret = RTNO_OK;
  //char intface;
  int8_t retval;
  switch(m_pPacketBuffer[INTERFACE]) {
  case DEACTIVATE:
    retval = EC_deactivate_component();
    if(retval < 0) ret = RTNO_ERROR;
    Transport_SendPacket(DEACTIVATE, 1, &ret);
    break;
  case EXECUTE:
    retval = EC_execute();
    if(retval < 0) ret = RTNO_ERROR;
    Transport_SendPacket(EXECUTE, 1, &ret);
    break;
  case SEND_DATA: {
      PortBase* pInPort = RTnoProfile_getInPort((char*)m_pPacketBuffer + 2 + 2, m_pPacketBuffer[2]);
      if(pInPort == NULL) {
        ret = RTNO_ERROR;   
        Transport_SendPacket(SEND_DATA, 1, &ret);
      } else {
        PortBuffer* pBuffer = pInPort->pPortBuffer;
        EC_suspend();
        pBuffer->push(pBuffer,&(m_pPacketBuffer[2 + 2 + m_pPacketBuffer[2]]), m_pPacketBuffer[2+1]);
        EC_resume();
        Transport_SendPacket(SEND_DATA, 1, &ret);
      }
    }
    break;
  default:
    break;
  }
}

