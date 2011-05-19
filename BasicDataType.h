/*******************************************
 * BasicDataType.h
 * @author Yuki Suga
 * @copyright Yuki Suga (ysuga.net) Nov, 10th, 2010.
 * @license LGPLv3
 *****************************************/

#ifndef BASIC_DATA_TYPE_HEADER_INCLUDED
#define BASIC_DATA_TYPE_HEADER_INCLUDED

#include "SequenceDataType.h"
#include "SequenceOctet.h"
#include "SequenceChar.h"
#include "SequenceBoolean.h"
#include "SequenceLong.h"
#include "SequenceDouble.h"
#include "SequenceFloat.h"
/*
typedef struct __Time__ {
  long sec;
  long usec;
}Time;
*/

class TimedData {
 public:
  virtual void* GetBuffer() { return 0;}
};

class TimedBoolean : public TimedData {
 public:
  char data;
  void* GetBuffer(){ return &data; }
  const static char typecode = 'b';
};

class TimedChar : public TimedData {
 public:
  char data;
  void* GetBuffer(){ return &data; }
  const static char typecode = 'c';
};

class TimedOctet : public TimedData {
 public:
  char data;
  void* GetBuffer(){ return &data; }
  const static char typecode = 'o';
};

class TimedLong : public TimedData{
  //  Time timestamp;
 public:
  long data;
  void* GetBuffer(){ return &data; }
  const static char typecode = 'l';
};

class TimedDouble : public TimedData {
//  Time timestamp;
 public:
  double data;
  void* GetBuffer(){ return &data; }
  const static char typecode = 'd';
};

class TimedFloat : public TimedData {
  //  unsigned char length;
public:
  float data;
  void* GetBuffer(){ return &data; }
  const static char typecode = 'f';
};

class TimedDataSeq {
 public:
  virtual SequenceDataType* GetBuffer(){return 0;}
};

class TimedOctetSeq : public TimedDataSeq {
  //  Time timestamp;
  //  long length;
 public:
  SequenceOctet data;
 SequenceDataType* GetBuffer() {return &data;}
  const static char typecode = 'O';
};

class TimedCharSeq : public TimedDataSeq {
  //  Time timestamp;
  //  long length;
 public:
  SequenceChar data;
 SequenceDataType* GetBuffer() {return &data;}
  const static char typecode = 'C';
};

class TimedBooleanSeq : public TimedDataSeq {
  //  Time timestamp;
  //  long length;
 public:
  SequenceBoolean data;
 SequenceDataType* GetBuffer() {return &data;}
  const static char typecode = 'B';
};

class TimedLongSeq : public TimedDataSeq {
  //  Time timestamp;
  //  long length;
 public:
  SequenceLong data;
 SequenceDataType* GetBuffer() {return &data;}
  const static char typecode = 'L';
};

class TimedFloatSeq : public TimedDataSeq {
  //  Time timestamp;
  //  long length;
  //  float* data;
 public:
  SequenceFloat data;
  SequenceDataType* GetBuffer() {return &data;}
  const static char typecode = 'F';
};

struct TimedDoubleSeq : public TimedDataSeq {
//  Time timestamp;
  //  long length;
  //  double* data;
 public:
  SequenceDouble data;
  SequenceDataType* GetBuffer() {return &data;}
  const static char typecode = 'D';
};


#endif
