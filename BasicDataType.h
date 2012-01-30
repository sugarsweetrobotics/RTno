/*******************************************
 * BasicDataType.h
 * @author Yuki Suga
 * @copyright Yuki Suga (ysuga.net) Nov, 10th, 2010.
 * @license LGPLv3
 *****************************************/

#ifndef BASIC_DATA_TYPE_HEADER_INCLUDED
#define BASIC_DATA_TYPE_HEADER_INCLUDED

#include <stdint.h>
#include "Sequence.h"

#pragma pack(1)
struct TimedBoolean  {
  static const char typeCode = 'b';
  char data;
};

struct TimedChar {
  static const char typeCode = 'c';
  char data;
};

struct TimedOctet {
  static const char typeCode = 'o';
  int8_t data;
};

struct TimedShort {
  static const char typeCode = 's';
  int16_t data;

};

struct TimedLong {
  static const char typeCode = 'l';
  int32_t data;
};

struct TimedDouble {
  static const char typeCode = 'd';
  double data;
};

struct TimedFloat {
  static const char typeCode = 'f';
  float data;
};


struct TimedOctetSeq {
  static const char typeCode = 'O';
  Sequence<int8_t> data;
};

struct TimedCharSeq {
  static const char typeCode = 'C';
  Sequence<char> data;
};

struct TimedBooleanSeq {
  static const char typeCode = 'B';
  Sequence<char> data;
};

struct TimedShortSeq {
  static const char typeCode = 'S';
  Sequence<int16_t> data;
};

struct TimedLongSeq {
  static const char typeCode = 'L';
  Sequence<int32_t> data;
};

struct TimedFloatSeq {
  static const char typeCode = 'F';
  Sequence<float> data;
};

struct TimedDoubleSeq {
  static const char typeCode = 'D';
  Sequence<double> data;
};


#endif
