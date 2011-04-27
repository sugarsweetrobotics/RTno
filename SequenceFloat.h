/*******************************************
 * SequenceFloat.h
 * @author Yuki Suga
 * @copyright Yuki Suga (ysuga.net) Nov, 10th, 2010.
 * @license LGPLv3
 *****************************************/

#ifndef SEQUENCE_FLOAT_HEADER_INCLUDED
#define SEQUENCE_FLOAT_HEADER_INCLUDED

class SequenceFloat : public SequenceDataType
{
 private:
  float* m_pData;
 public:
 SequenceFloat() : SequenceDataType((void**)&m_pData) {

  }
  ~SequenceFloat(){}

  float& operator[](int index) {
    return m_pData[index];
  }

};

#endif
