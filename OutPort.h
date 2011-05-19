#ifndef OUTPORT_HEADER_INCLUDED
#define OUTPORT_HEADER_INCLUDED

/*******************************************
 * OutPort.h
 * @author Yuki Suga
 * @copyright Yuki Suga (ysuga.net) Nov, 10th, 2010.
 * @license LGPLv3
 *****************************************/

#include "OutPortBase.h"

class OutPort : public OutPortBase
{
 private:
  //  void* m_pData;

 public:
  OutPort(char* name, TimedBoolean& pData);
  OutPort(char* name, TimedChar& pData);
  OutPort(char* name, TimedOctet& pData);

  OutPort(char* name, TimedLong& pData);
  OutPort(char* name, TimedFloat& pData);
  OutPort(char* name, TimedDouble& pData);

  OutPort(char* name, TimedBooleanSeq& pData);
  OutPort(char* name, TimedCharSeq& pData);
  OutPort(char* name, TimedOctetSeq& pData);

  OutPort(char* name, TimedLongSeq& pData);
  OutPort(char* name, TimedFloatSeq& pData);
  OutPort(char* name, TimedDoubleSeq& pData);

  ~OutPort();

 public:
  int SizeofData();
  int write();
};


#endif
