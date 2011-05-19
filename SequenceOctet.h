/*******************************************
 * SequenceOctet.h
 * @author Yuki Suga
 * @copyright Yuki Suga (ysuga.net) Nov, 10th, 2010.
 * @license LGPLv3
 *****************************************/

#ifndef SEQUENCE_OCTET_HEADER_INCLUDED
#define SEQUENCE_OCTET_HEADER_INCLUDED

class SequenceOctet : public SequenceDataType
{
 private:
  char* m_pData;
 public:
 SequenceOctet() : SequenceDataType((void**)&m_pData) {

  }
  ~SequenceOctet(){}
  int SizeofData() { return 4; }
  char& operator[](int index) {
    return m_pData[index];
  }

};

#endif
