/*******************************************
 * Packet.h
 * @author Yuki Suga
 * @copyright Yuki Suga (ysuga.net) Nov, 10th, 2010.
 * @license LGPLv3
 *****************************************/

#ifndef PACKET_HEADER_INCLUDED
#define PACKET_HEADER_INCLUDED



// Packet Settings
#define PKT_ADDR_INTERFACE 0
#define PKT_ADDR_DATA_LENGTH 1
#define PKT_ADDR_SOURCE_ADDR 2
#define PKT_SOURCE_ADDR_SIZE 4
#define PKT_ADDR_SOURCE_PORT 6
#define PKT_ADDR_TARGET_PORT 7
#define PKT_HEADER_SIZE (2+PKT_SOURCE_ADDR_SIZE+2)
#define PKT_ADDR_DATA_START_ADDR PKT_HEADER_SIZE

// Return Codes
#define RTNO_RTC_OK 0
#define RTNO_RTC_ERROR -1
#define RTNO_RTC_PRECONDITION_NOT_MET -2
#define RTNO_RTC_PACKET_TIMEOUT -3
#define RTNO_RTC_CHECKSUM_ERROR -4


// RTC's state
#define  RTC_STATE_CREATED 'C'
#define  RTC_STATE_INACTIVE 'I'
#define  RTC_STATE_ACTIVE 'A'
#define  RTC_STATE_ERROR 'E'
#define  RTC_STATE_NONE 'N'


// DataPort Index Number.
// In RTno, ControlPort is defined to activate/deactivate/reset,
// to specify its condition, to request RTnoProfile packet, etc.
#define CONTROL_PORT_INDEX 0xFE
#define ALL_PORT_INDEX 0xFF

// Interface
// The first byte of the RTno packet is Interface packet.
// This defines the packet's job.

// For Error Code
#define UNKNOWN_INTERFACE 'P'
#define PACKET_ERROR 'F' // Check sum, timeout, and some error.

// For ControlPort
#define CONTROL_INITIALIZE 'I'
#define CONTROL_ACTIVATE 'A'
#define CONTROL_DEACTIVATE 'D'
#define CONTROL_EXECUTE 'E'
#define CONTROL_RESET 'R'
#define CONTROL_GET_PROFILE 'Z'
#define CONTROL_GET_CONTEXT 'B'
#define CONTROL_GET_STATUS 'X'
#define CONTROL_INPORT_CONNECT 'M'
#define CONTROL_OUTPORT_CONNECT 'N'
#define CONTROL_INPORT_DISCONNECT 'H'
#define CONTROL_OUTPORT_DISCONNECT 'J'


// For Data Port Packet
#define DATAPORT_DATA 'G'

// For RTno Profile
#define PROFILE_INPORT 'P'
#define PROFILE_OUTPORT 'Q'


// Communication Settings
#define PACKET_WAITING_TIME 100 // ms
#define PACKET_WAITING_DELAY 100 //us
#define PACKET_WAITING_COUNT (PACKET_WAITING_TIME*1000/PACKET_WAITING_DELAY)


// Type Codes
#define TYPECODE_TIMED_BOOLEAN 'b'
#define TYPECODE_TIMED_CHAR 'c'
#define TYPECODE_TIMED_OCTET 'o'
#define TYPECODE_TIMED_LONG 'l'
#define TYPECODE_TIMED_FLOAT 'f'
#define TYPECODE_TIMED_DOUBLE 'd'
#define TYPECODE_TIMED_BOOLEAN_SEQ 'B'
#define TYPECODE_TIMED_CHAR_SEQ 'C'
#define TYPECODE_TIMED_OCTET_SEQ 'O'
#define TYPECODE_TIMED_LONG_SEQ 'L'
#define TYPECODE_TIMED_FLOAT_SEQ 'F'
#define TYPECODE_TIMED_DOUBLE_SEQ 'D'

#endif
