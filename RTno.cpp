/*******************************************
 * RTno.cpp
 * @author Yuki Suga
 * @copyright Yuki Suga (ysuga.net) Nov, 10th, 2010.
 * @license LGPLv3
 *****************************************/
#define RTNO_SUBMODULE_DEFINE
#include <Arduino.h>
#include <stdint.h>

#include "RTno.h"
#include "Packet.h"
#include "PacketBuffer.h"
#include "Connection.h"
#include "Transport.h"
#include "RTnoProfile.h"

using namespace RTno;

// global variables
// module private variables.
#define PRIVATE static

// static value declaration.
void(*SerialDevice_init)(const char* address);
void(*SerialDevice_putc)(const char c);
int8_t(*SerialDevice_receive)();
uint8_t(*SerialDevice_available)();
char(*SerialDevice_getc)();
void(*SerialDevice_setTarget)(const char* address);
uint8_t(*SerialDevice_read)(int8_t* dst, const uint8_t maxSize);
void(*SerialDevice_write)(const int8_t* src, const uint8_t size);


PRIVATE char m_Address[4];
PRIVATE char m_pFromInfo[4];
//PRIVATE int8_t m_pPacketBuffer[PACKET_BUFFER_SIZE];
PRIVATE int8_t* m_pPacketBuffer;
/*
 * Send Profile Data
 */
PRIVATE void _SendProfile();
PRIVATE void _SendOutPortData(PortBase* pOutPort, uint8_t index);
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
    PacketBuffer_init(128);
    m_pPacketBuffer = PacketBuffer_getBuffer();
    m_Address[0] = 'U', m_Address[1] = 'A', m_Address[2] = 'R', m_Address[3] = 'T';
    PacketBuffer_setAddress((int8_t*)m_Address);
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
  
  //  ret = Transport_ReceivePacket(m_pPacketBuffer, m_pFromInfo);
  ret = Transport_ReceivePacket();

  if(ret < 0) { // Timeout Error or Checksum Error
    PacketBuffer_clear();
    PacketBuffer_setInterface(PACKET_ERROR);
    PacketBuffer_push((int8_t*)&ret, 1);
    PacketBuffer_seal();
    Transport_SendPacket(m_pFromInfo);
  } else if (ret == 0) {
    
  } else if (ret > 0) { // Packet is successfully received
    uint8_t interface_c = 0;
    int8_t retval = RTNO_OK;
    int8_t state = EC_get_component_state();
    switch(PacketBuffer_getInterface()) {
    case GET_PROFILE:
      _SendProfile();
      break;
    case GET_STATUS:
      interface_c = GET_STATUS;
      retval = state;
      break;
    case GET_CONTEXT:
      interface_c = GET_CONTEXT;
      retval = EC_get_type();
      break;
    case DEACTIVATE:
      ret = EC_deactivate_component();
      if(ret < 0) retval = RTNO_ERROR;
      interface_c = DEACTIVATE;
      break;
    case ACTIVATE:
      ret = EC_activate_component();
      if(ret < 0) retval = RTNO_ERROR;
      interface_c = ACTIVATE;
      break;
    case EXECUTE:
      if(state == RTC_STATE_ACTIVE) {
	ret = EC_execute();
      } else if (state == RTC_STATE_ERROR) {
	ret = EC_error();
      }
      if(ret < 0) retval = RTNO_ERROR;
      interface_c = EXECUTE;
      break;
    case RESET:
      ret = EC_reset_component();
      if(ret < 0) retval = RTNO_ERROR;
      interface_c = RESET;
      break;
    case SEND_DATA:
      if(Connection_isConnected(m_pFromInfo)) {
	_ReceiveInPortData();
      }
      break;

    default:
      break;
    }// switch

    if(interface_c != 0) {
      PacketBuffer_clear();
      PacketBuffer_setInterface(interface_c);
      PacketBuffer_push((int8_t*)&retval, 1);
      PacketBuffer_seal();
      Transport_SendPacket(m_pFromInfo);
    }
  }
  
  int numOutPort = RTnoProfile_getNumOutPort();
  for(int i = 0;i < numOutPort;i++) {
    EC_suspend();
    PortBase* pOutPort = RTnoProfile_getOutPortByIndex(i);
    if(pOutPort->pPortBuffer->hasNext(pOutPort->pPortBuffer)) {
      _SendOutPortData(pOutPort, i); 
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
  char* destination = "UART";
  for(uint8_t i = 0;i < RTnoProfile_getNumInPort();i++) {
    PortBase* inPort = RTnoProfile_getInPortByIndex(i);
    PacketBuffer_clear();
    PacketBuffer_setInterface(ADD_INPORT);
    PacketBuffer_push((int8_t*)&(inPort->typeCode), 1);
    PacketBuffer_push((int8_t*)inPort->pName, strlen(inPort->pName));
    PacketBuffer_seal();
    Transport_SendPacket((char*)destination);
  }

  for(uint8_t i = 0;i < RTnoProfile_getNumOutPort();i++) {
    PortBase* outPort = RTnoProfile_getOutPortByIndex(i);
    PacketBuffer_clear();
    PacketBuffer_setInterface(ADD_OUTPORT);
    PacketBuffer_push((int8_t*)&(outPort->typeCode), 1);
    PacketBuffer_push((int8_t*)outPort->pName, strlen(outPort->pName));
    PacketBuffer_seal();
    Transport_SendPacket((char*)destination);
  }

  PacketBuffer_clear();
  PacketBuffer_setInterface(GET_PROFILE);
  PacketBuffer_push((int8_t*)&ret, 1);
  PacketBuffer_seal();
  Transport_SendPacket((char*)destination);
}


void _SendOutPortData(PortBase* pOutPort, uint8_t index)
{
  char myAddress[4] = {'U', 'A', 'R', 'T'};
  char *destination = "UART";
  uint8_t nameLen = strlen(pOutPort->pName);
  uint8_t dataLen = pOutPort->pPortBuffer->getNextDataSize(pOutPort->pPortBuffer);
  
  PacketBuffer_clear();
  PacketBuffer_setInterface(RECEIVE_DATA);
  PacketBuffer_setSourcePortIndex(index);
  PacketBuffer_push((int8_t*)&dataLen, 1);
  PacketBuffer_push((int8_t*)(pOutPort->pPortBuffer->get(pOutPort->pPortBuffer)), dataLen);
  PacketBuffer_seal();
  pOutPort->pPortBuffer->pop(pOutPort->pPortBuffer, NULL, dataLen);

  ConnectionIterator_init(pOutPort);
  PacketBuffer_setTargetPortIndex(0xCC);
  while(ConnectionIterator_hasNext()) {
    ConnectionIterator_next();
    Transport_SendPacket(destination);
  }
}

void _ReceiveInPortData() {
  int8_t ret = RTNO_OK;
  PortBase* pInPort = RTnoProfile_getInPortByIndex(PacketBuffer_getTargetPortIndex());
  if(pInPort != NULL) {
    EC_suspend();
    int8_t* pDataBuffer = PacketBuffer_getDataBuffer();
    
    pInPort->pPortBuffer->push(pInPort->pPortBuffer,
			       pDataBuffer+1,
			       pDataBuffer[0]);
    EC_resume();
  }
}





