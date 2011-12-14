#ifndef INPORT_HEADER_INCLUDED
#define INPORT_HEADER_INCLUDED

/*******************************************
 * InPort.h
 * @author Yuki Suga
 * @copyright Yuki Suga (ysuga.net) Nov, 10th, 2010.
 * @license LGPLv3
 *****************************************/

#include "InPortBase.h"

class InPort : public InPortBase {
 private:
  //  int isSequence;
 public:
  InPort(char* name, TimedOctet &Data);
  InPort(char* name, TimedBoolean &Data);
  InPort(char* name, TimedChar &Data);

  InPort(char* name, TimedLong &Data);
  InPort(char* name, TimedFloat &Data);
  InPort(char* name, TimedDouble &Data);

  InPort(char* name, TimedOctetSeq &Data);
  InPort(char* name, TimedBooleanSeq &Data);
  InPort(char* name, TimedCharSeq &Data);

  InPort(char* name, TimedLongSeq &Data);
  InPort(char* name, TimedFloatSeq &Data);
  InPort(char* name, TimedDoubleSeq &Data);

  ~InPort();

 public:
  int isNew();
  int read();
  int SizeofData();
  



};



#endif
