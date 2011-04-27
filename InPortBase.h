/*******************************************
 * InPortBase.h
 * @author Yuki Suga
 * @copyright Yuki Suga (ysuga.net) Nov, 10th, 2010.
 * @license LGPLv3
 *****************************************/

#ifndef INPORT_BASE_HEADER_INCLUDED
#define INPORT_BASE_HEADER_INCLUDED

#include "PortBase.h"

class InPortBase : public PortBase {
 public:

 public:
 InPortBase(char *name) : PortBase(name){}

  //  virtual bool isNew() = 0;
  //  virtual bool read(char* dst, int size) = 0;

};
#endif
