/*******************************************
 * SequenceLong.h
 * @author Yuki Suga
 * @copyright Yuki Suga (ysuga.net) Nov, 10th, 2010.
 * @license LGPLv3
 *****************************************/

#ifndef SEQUENCE_LONG_HEADER_INCLUDED
#define SEQUENCE_LONG_HEADER_INCLUDED

class SequenceLong : public SequenceDataType
{
 private:
  long* m_pData;
 public:
 SequenceLong() : SequenceDataType((void**)&m_pData) {

  }
  ~SequenceLong(){}
  int SizeofData() { return 4; }
  long& operator[](int index) {
    return m_pData[index];
  }

};

#endif
