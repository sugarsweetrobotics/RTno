/*******************************************
 * SequenceBoolean.h
 * @author Yuki Suga
 * @copyright Yuki Suga (ysuga.net) Nov, 10th, 2010.
 * @license LGPLv3
 *****************************************/

#ifndef SEQUENCE_BOOLEAN_HEADER_INCLUDED
#define SEQUENCE_BOOLEAN_HEADER_INCLUDED

class SequenceBoolean : public SequenceDataType
{
 private:
  char* m_pData;
 public:
 SequenceBoolean() : SequenceDataType((void**)&m_pData) {

  }
  ~SequenceBoolean(){}
  int SizeofData() { return 1; }
  char& operator[](int index) {
    return m_pData[index];
  }

};

#endif
