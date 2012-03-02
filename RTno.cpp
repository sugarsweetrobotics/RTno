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
int8_t(*SerialDevice_receive)(int8_t* sourceInfo);
uint8_t(*SerialDevice_available)();
uint8_t(*SerialDevice_read)(int8_t* dst, const uint8_t maxSize);
int8_t(*SerialDevice_write)(const int8_t* target, const int8_t* src, const uint8_t size);

/*
 * Send Profile Data
 */
PRIVATE int8_t _SendProfile(const int8_t* destination);
PRIVATE void _SendOutPortData(PortBase* pOutPort, uint8_t index);
PRIVATE void _ReceiveInPortData(); 
PRIVATE int8_t _ConnectInPort();
PRIVATE int8_t _ConnectOutPort();
PRIVATE void _DisconnectInPort();
PRIVATE void _DisconnectOutPort();

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
    PacketBuffer_setAddress((int8_t*)"UART");
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
  int8_t sourceAddress[PKT_SOURCE_ADDR_SIZE];
  ret = Transport_ReceivePacket();
  memcpy(sourceAddress, PacketBuffer_getAddress(), PKT_SOURCE_ADDR_SIZE);
  int8_t state = EC_get_component_state();
  if(ret < 0) { // Timeout Error or Checksum Error
    PacketBuffer_clear();
    PacketBuffer_setInterface(PACKET_ERROR);
    PacketBuffer_setAddress((int8_t*)"UART");
    PacketBuffer_push((int8_t*)&ret, 1);
    PacketBuffer_seal();
    Transport_SendPacket(sourceAddress);
  } else if (ret == 0) {
    
  } else if (ret > 0) { // Packet is successfully received
    //    Serial.print("Receive OK. Interface= ");
    //    Serial.print(PacketBuffer_getInterface());
    //    Serial.print("\r\n");

    if(PacketBuffer_getTargetPortIndex() == CONTROL_PORT_INDEX) {
      int8_t interface_c = PacketBuffer_getInterface();
      switch(interface_c) {
      case CONTROL_INPORT_CONNECT:
	if(_ConnectInPort() < 0) ret = RTNO_RTC_ERROR;
	else ret = RTNO_RTC_OK;
	break;
      case CONTROL_OUTPORT_CONNECT:
	if(_ConnectOutPort() < 0) ret = RTNO_RTC_ERROR;
	else ret = RTNO_RTC_OK;
	break;
      case CONTROL_INPORT_DISCONNECT:
	_DisconnectInPort();
	ret = RTNO_RTC_OK;
	break;
      case CONTROL_OUTPORT_DISCONNECT:
	_DisconnectOutPort();
	ret = RTNO_RTC_OK;
	break;
      case CONTROL_GET_PROFILE:
	_SendProfile(sourceAddress);
	ret = RTNO_RTC_OK;
	break;
      case CONTROL_GET_STATUS:
	ret = state;
	break;
      case CONTROL_GET_CONTEXT:
	ret = EC_get_type();
	break;
      case CONTROL_DEACTIVATE:
	ret = EC_deactivate_component();
	break;
      case CONTROL_ACTIVATE:
	ret = EC_activate_component();
	break;
      case CONTROL_EXECUTE:
	if(state == RTC_STATE_ACTIVE) {
	  ret = EC_execute();
	} else if (state == RTC_STATE_ERROR) {
	  ret = EC_error();
	}
	break;
      case CONTROL_RESET:
	ret = EC_reset_component();
	break;
      default:
	ret = interface_c;
	interface_c = UNKNOWN_INTERFACE;
	break;
      }
      PacketBuffer_clear();
      PacketBuffer_setInterface(interface_c);
      PacketBuffer_setAddress((int8_t*)"UART");
      PacketBuffer_push((int8_t*)&ret, 1);
      PacketBuffer_seal();
      Transport_SendPacket(sourceAddress);
      
    } else {
      switch(PacketBuffer_getInterface()) {
      case DATAPORT_DATA:
	_ReceiveInPortData();
	break;
	
      default:
	break;
      }// switch
    }
  }
  
  if(state == RTC_STATE_ACTIVE) {
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
PRIVATE int8_t _SendProfile(const int8_t* destination) {
  int8_t ret = RTNO_RTC_OK;
  PacketBuffer_setAddress((int8_t*)"UART");
  for(uint8_t i = 0;i < RTnoProfile_getNumInPort();i++) {
    PortBase* inPort = RTnoProfile_getInPortByIndex(i);
    PacketBuffer_clear();
    PacketBuffer_setInterface(PROFILE_INPORT);
    PacketBuffer_push((int8_t*)&(inPort->typeCode), 1);
    PacketBuffer_push((int8_t*)inPort->pName, strlen(inPort->pName));
    PacketBuffer_seal();
    if(Transport_SendPacket(destination) < 0) {
      return -1;
    }
  }

  for(uint8_t i = 0;i < RTnoProfile_getNumOutPort();i++) {
    PortBase* outPort = RTnoProfile_getOutPortByIndex(i);
    PacketBuffer_clear();
    PacketBuffer_setInterface(PROFILE_OUTPORT);
    PacketBuffer_push((int8_t*)&(outPort->typeCode), 1);
    PacketBuffer_push((int8_t*)outPort->pName, strlen(outPort->pName));
    PacketBuffer_seal();
    if(Transport_SendPacket(destination) < 0) {
      return -1;
    }
  }
  return 0;
}


void _SendOutPortData(PortBase* pOutPort, uint8_t index)
{
  char myAddress[4] = {'U', 'A', 'R', 'T'};
  char *destination = "UART";
  uint8_t nameLen = strlen(pOutPort->pName);
  uint8_t dataLen = pOutPort->pPortBuffer->getNextDataSize(pOutPort->pPortBuffer);
  
  PacketBuffer_clear();
  PacketBuffer_setInterface(DATAPORT_DATA);

  PacketBuffer_setSourcePortIndex(index);
  PacketBuffer_push((int8_t*)(pOutPort->pPortBuffer->get(pOutPort->pPortBuffer)), dataLen);
  PacketBuffer_seal();
  pOutPort->pPortBuffer->pop(pOutPort->pPortBuffer, NULL, dataLen);

  for(int i = 0;i < ConnectionList_size(pOutPort->pConnectionList);i++) {
    Connection* connection = ConnectionList_item(pOutPort->pConnectionList, i);
    PacketBuffer_setTargetPortIndex(connection->targetPort);
    PacketBuffer_seal();
    Transport_SendPacket(connection->targetAddress);
  }
}

static char sourceIP[] = {1, 1, 1, 1};

int8_t _ConnectPort(PortBase* portBase) {
  if(portBase == NULL) return -1;
  int8_t* data = PacketBuffer_getDataBuffer();
  Connection* connection= ConnectionList_search(portBase->pConnectionList, data+1, *((uint8_t*)data+1+PKT_SOURCE_ADDR_SIZE));
  if(connection == NULL) {
    if(strncmp((char*)data+1, sourceIP, PKT_SOURCE_ADDR_SIZE) == 0) {
      if(ConnectionList_addConnection(portBase->pConnectionList, Connection_create(PacketBuffer_getAddress(), *((uint8_t*)data+1+PKT_SOURCE_ADDR_SIZE))) < 0) {
	return -1;
      }
    } else {
      if(ConnectionList_addConnection(portBase->pConnectionList, Connection_create(data+1, *((uint8_t*)data+1+PKT_SOURCE_ADDR_SIZE))) < 0) {
	return -1;
      }
    }
  }
  return 0;
}

int8_t _ConnectInPort() {
  int8_t* data = PacketBuffer_getDataBuffer();
  PortBase* pPort = RTnoProfile_getInPortByIndex(data[0]);
  return _ConnectPort(pPort);
}

int8_t _ConnectOutPort() {
  int8_t* data = PacketBuffer_getDataBuffer();
  PortBase* pPort = RTnoProfile_getOutPortByIndex(data[0]);
  return _ConnectPort(pPort);
}


void _DisconnectPort(PortBase* portBase) {
  int8_t* data = PacketBuffer_getDataBuffer();
  Connection* connection= ConnectionList_search(portBase->pConnectionList, data+1, *((uint8_t*)data+1+PKT_SOURCE_ADDR_SIZE));
  if(connection != NULL) {
    ConnectionList_remove(portBase->pConnectionList, connection);
  }
}
  
void _DisconnectInPort() {
  int8_t* data = PacketBuffer_getDataBuffer();
  PortBase* pPort = RTnoProfile_getInPortByIndex(data[0]);
  _DisconnectPort(pPort);
}

void _DisconnectOutPort() {
  int8_t* data = PacketBuffer_getDataBuffer();
  PortBase* pPort = RTnoProfile_getOutPortByIndex(data[0]);
  _DisconnectPort(pPort);
}

void _ReceiveInPortData() {
  int8_t ret = RTNO_RTC_OK;
  PortBase* pInPort = RTnoProfile_getInPortByIndex(PacketBuffer_getTargetPortIndex());
  
  if(ConnectionList_search(pInPort->pConnectionList, PacketBuffer_getAddress(), PacketBuffer_getSourcePortIndex()) != NULL) {
    if(pInPort != NULL) {
      EC_suspend();
      pInPort->pPortBuffer->push(pInPort->pPortBuffer,
				 PacketBuffer_getDataBuffer(),
				 PacketBuffer_getDataLength());
      EC_resume();
    }
  }
}





