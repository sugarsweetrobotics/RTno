/*******************************************
 * SequenceChar.h
 * @author Yuki Suga
 * @copyright Yuki Suga (ysuga.net) Nov, 10th, 2010.
 * @license LGPLv3
 *****************************************/

#ifndef SEQUENCE_CHAR_HEADER_INCLUDED
#define SEQUENCE_CHAR_HEADER_INCLUDED

class SequenceChar : public SequenceDataType
{
 private:
  char* m_pData;
 public:
 SequenceChar() : SequenceDataType((void**)&m_pData) {

  }
  ~SequenceChar(){}
  int SizeofData() { return 1; }
  char& operator[](int index) {
    return m_pData[index];
  }

};

#endif
