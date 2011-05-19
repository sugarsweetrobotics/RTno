/*******************************************
 * SequenceDouble.h
 * @author Yuki Suga
 * @copyright Yuki Suga (ysuga.net) Nov, 10th, 2010.
 * @license LGPLv3
 *****************************************/

#ifndef SEQUENCE_DOUBLE_HEADER_INCLUDED
#define SEQUENCE_DOUBLE_HEADER_INCLUDED

class SequenceDouble : public SequenceDataType
{
 private:
  double* m_pData;
 public:
 SequenceDouble() : SequenceDataType((void**)&m_pData) {

  }
  ~SequenceDouble(){}
  int SizeofData() { return 4; }

  double& operator[](int index) {
    return m_pData[index];
  }
};

#endif
