/*******************************************
 * RTno.cpp
 * @author Yuki Suga
 * @copyright Yuki Suga (ysuga.net) Nov, 10th, 2010.
 * @license LGPLv3
 *****************************************/
#define RTNO_SUBMODULE_DEFINE
#include <Arduino.h>



#include "RTno.h"
#include "Packet.h"

#include "Transport.h"
#include "UARTTransport.h"
#include "EtherTcpTransport.h"
#include "RTnoProfile.h"
#include "Timer1ExecutionContext.h"
#include "ProxySyncEC.h"

using namespace RTno;

// global variables
config_str conf;
exec_cxt_str exec_cxt;

// module private variables.
#define PRIVATE static

// static value declaration.
void(*SerialDevice_putc)(const char c);
unsigned char(*SerialDevice_available)();
char(*SerialDevice_getc)();

PRIVATE char m_pPacketBuffer[PACKET_BUFFER_SIZE];

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


void Connection_setup();

/**
 * Arduino Setup Routine.
 * This function is called when arduino device is turned on.
 */
void setup() {
  RTnoProfile_init();
  // This function must be called first.
  rtcconf();
  if(onInitialize() == RTC_OK) {
    Connection_setup();
    Transport_init();//g_pSerialDevice);
    switch(exec_cxt.periodic.type) {
    case Timer1ExecutionContext:
      Timer1EC_init(exec_cxt.periodic.rate);
      break;
    default:
    case ProxySynchronousExecutionContext:
      ProxySyncEC_init();
      break;
    }

    EC_start();
  } else {

  }
}


/**
 * Arduino Loop routine.
 * This function is repeadedly called when arduino is turned on.
 */
void loop() {
  char ret;
  ret = Transport_ReceivePacket((unsigned char*)m_pPacketBuffer);

  if(ret < 0) { // Timeout Error or Checksum Error
    Transport_SendPacket(PACKET_ERROR, 1, &ret);
  } else if (ret == 0) {
  } else if (ret > 0) { // Packet is successfully received
    if (m_pPacketBuffer[INTERFACE] == GET_PROFILE) {
      _SendProfile();
    } else if(m_pPacketBuffer[INTERFACE] == GET_STATUS) {
      char state = EC_get_component_state();
      Transport_SendPacket(GET_STATUS, 1, &state);
    } else if(m_pPacketBuffer[INTERFACE] == GET_CONTEXT) {
      Transport_SendPacket(GET_CONTEXT, 1, (char*)&(exec_cxt.periodic.type));
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
	Transport_SendPacket(m_pPacketBuffer[INTERFACE], 1, &ret);
	break;
      default: // if m_Condition is unknown...
	
	break;
      }
    }
  }

  
  //  int numOutPort = m_Profile.getNumOutPort();
  int numOutPort = RTnoProfile_getNumOutPort();
  for(int i = 0;i < numOutPort;i++) {
    //    m_pExecutionContext->suspend();
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
    //    if(exec_cxt.periodic.type == Timer1ExecutionContext) {
    //m_pExecutionContext->resume();
    EC_resume();
    //    }
  }
  
}

/**
 * add InPort data to Profile.
 */
void addInPort(InPortBase& Port)
{
  RTnoProfile_addInPort(&Port);
  //  m_Profile.addInPort(Port);
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
  char ret = RTNO_OK;
  for(int i = 0;i < RTnoProfile_getNumInPort();i++) {
    PortBase* inPort = RTnoProfile_getInPortByIndex(i);
    int nameLen = strlen(inPort->pName);
    m_pPacketBuffer[0] = inPort->typeCode;
    memcpy(&(m_pPacketBuffer[1]), inPort->pName, nameLen);
    Transport_SendPacket(ADD_INPORT, 1+nameLen, m_pPacketBuffer);
  }

  for(int i = 0;i < RTnoProfile_getNumOutPort();i++) {
    PortBase* outPort = RTnoProfile_getOutPortByIndex(i);
    int nameLen = strlen(outPort->pName);
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
  char ret = RTNO_OK;
  //  char retval = m_pExecutionContext->error();
  char retval = EC_error();
  if(retval < 0) ret = RTNO_ERROR;
  /**
  if(m_pPacketBuffer[INTERFACE] == ONERROR) {
    if(exec_cxt.periodic.type == ProxySynchronousExecutionContext) {
      onError();
      intface = ONERROR;
      ret = RTNO_OK;
    }
  } else if(m_pPacketBuffer[INTERFACE] == RESET) {
    intface = RESET;
    if(onReset() == RTC_OK) {
      m_Condition = INACTIVE;
      ret = RTNO_OK;

    } else {
      m_Condition = ERROR;
    }

    }*/
  Transport_SendPacket(intface, 1, &ret);
}


/** 
 * Packet Handler in Inactive State
 */
PRIVATE void _PacketHandlerOnInactive() {

  char ret = RTNO_OK;
  //  char retval = m_pExecutionContext->activate_component();
  char retval = EC_activate_component();
  if(retval < 0) ret = RTNO_ERROR;
  /*
  if(m_pPacketBuffer[INTERFACE] == ACTIVATE) {
    if(onActivated() == RTC_OK) {
      m_Condition = ACTIVE;
      ret = RTNO_OK;
    } else {
      m_Condition = ERROR;
    }

    }*/
  Transport_SendPacket(ACTIVATE, 1, &ret);
}

/**
 * Packet Handler in Active State.
 */
PRIVATE void _PacketHandlerOnActive() {
  char ret = RTNO_OK;
  char intface;
  char retval;
  switch(m_pPacketBuffer[INTERFACE]) {
  case DEACTIVATE:
    //    retval = m_pExecutionContext->deactivate_component();
    retval = EC_deactivate_component();
    if(retval < 0) ret = RTNO_ERROR;
    /*
    if(exec_cxt.periodic.type == Timer1ExecutionContext) {
      //      m_pTimer1EC->suspend();
    }
    intface = DEACTIVATE;
    onDeactivated();
    m_Condition = INACTIVE;
    ret = RTNO_OK;
    */
    Transport_SendPacket(DEACTIVATE, 1, &ret);
    break;
  case EXECUTE:
    //    retval = m_pExecutionContext->execute();
    retval = EC_execute();
    if(retval < 0) ret = RTNO_ERROR;
    /*
    intface = EXECUTE;
    if(exec_cxt.periodic.type == ProxySynchronousExecutionContext) {
      if(onExecute() == RTC_OK) {
	ret = RTNO_OK;
      } else {
	m_Condition = ERROR;
      }

    }
    */
    Transport_SendPacket(EXECUTE, 1, &ret);
    break;
  case SEND_DATA: {
      PortBase* pInPort = RTnoProfile_getInPort(
					    &(m_pPacketBuffer[DATA_START_ADDR+2]),
					    m_pPacketBuffer[DATA_START_ADDR]);
      if(pInPort == NULL) {

      } else {
	//	m_pExecutionContext->suspend();
	PortBuffer* pBuffer = pInPort->pPortBuffer;
	EC_suspend();
	pBuffer->push(pBuffer,&(m_pPacketBuffer[DATA_START_ADDR+2+m_pPacketBuffer[DATA_START_ADDR]]), m_pPacketBuffer[DATA_START_ADDR+1]);
	//m_pExecutionContext->resume();
	EC_resume();
	Transport_SendPacket(SEND_DATA, 1, &ret);
      }
    }
    break;
  default:
    break;
  }

}

