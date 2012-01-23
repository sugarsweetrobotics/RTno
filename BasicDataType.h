/*******************************************
 * BasicDataType.h
 * @author Yuki Suga
 * @copyright Yuki Suga (ysuga.net) Nov, 10th, 2010.
 * @license LGPLv3
 *****************************************/

#ifndef BASIC_DATA_TYPE_HEADER_INCLUDED
#define BASIC_DATA_TYPE_HEADER_INCLUDED

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
  char data;
};

struct TimedLong {
  static const char typeCode = 'l';
  long data;
};

struct TimedDouble {
  static const char typeCode = 'd';
  double data;
};

class TimedFloat {
  float data;
};


struct TimedOctetSeq {
  Sequence<char> data;
};

struct TimedCharSeq {
  Sequence<char> data;
};

struct TimedBooleanSeq {
  Sequence<char> data;
};

struct TimedLongSeq {
  Sequence<long> data;
};

struct TimedFloatSeq {
  Sequence<float> data;
};

struct TimedDoubleSeq {
  Sequence<double> data;
};


#endif
