/*******************************************
 * OutPortBase.h
 * @author Yuki Suga
 * @copyright Yuki Suga (ysuga.net) Nov, 10th, 2010.
 * @license LGPLv3
 *****************************************/


#ifndef OUTPORT_BASE_HEADER_INCLUDED
#define OUTPORT_BASE_HEADER_INCLUDED

#include "PortBase.h"

class OutPortBase : public PortBase {

 public:
 OutPortBase(char* name): PortBase(name) {}

 public:
  //  virtual bool write(char* src, int size) = 0;

};

#endif
