#ifndef SEQUENCE_HEADER_INCLUDED
#define SEQUENCE_HEADER_INCLUDED

#include <stdlib.h>

class SequenceBase {
 protected:
    unsigned char m_length;

 public:
  virtual unsigned char length() {
    return m_length;
  }
  
  virtual void length(unsigned char len) = 0;// {m_length=6;};

};


template<typename T>
class Sequence : public SequenceBase {
  T *m_ptr;

 public:
  Sequence() {m_ptr = 0;}
  virtual void length(unsigned char len) {
    m_length = len;
    free((void*)m_ptr);
    m_ptr = (T*)malloc(len * sizeof(T));
  }

  virtual unsigned char length() {
    return SequenceBase::length();
  }

  T& operator[](int index) {
    return m_ptr[index];
  }

  //T* operator&() {
  //  return m_ptr;
  //}
};


#endif //#ifndef SEQUENCE_HEADER_INCLUDED
