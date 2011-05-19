/*******************************************
 * SequenceDataType.h
 * @author Yuki Suga
 * @copyright Yuki Suga (ysuga.net) Nov, 10th, 2010.
 * @license LGPLv3
 *****************************************/

#ifndef SEQUENCE_DATA_TYPE_HEADER_INCLUDED
#define SEQUENCE_DATA_TYPE_HEADER_INCLUDED

class SequenceDataType {
 private:
  void** m_ptrptr;
  int len;
 public:
  SequenceDataType(void** ptrptr); 
  ~SequenceDataType();
 public:
  virtual int SizeofData() {return 0;}
  void length(int size) ;
  int length() {return len;}
  void* GetBuffer() { return *m_ptrptr; }
};

#endif
