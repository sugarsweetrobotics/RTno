#ifndef SEQUENCE_HEADER_INCLUDED
#define SEQUENCE_HEADER_INCLUDED

#include <stdint.h>
#include <stdlib.h>

class SequenceBase {
 protected:
    uint8_t m_length;

 public:
  virtual uint8_t length() {
    return m_length;
  }
  
  virtual void length(uint8_t len) {};

  virtual void* getData() = 0;
};


template<typename T>
class Sequence : public SequenceBase {
  T *m_ptr;

 public:
  Sequence() {m_ptr = 0;}
  virtual void length(uint8_t len) {
    m_length = len;
    free((void*)m_ptr);
    m_ptr = (T*)malloc(len * sizeof(T));
  }

  virtual uint8_t length() {
    return SequenceBase::length();
  }
  T& operator[](uint8_t index) {
    return m_ptr[index];
  }

  virtual void* getData() { return m_ptr; }
};


#endif //#ifndef SEQUENCE_HEADER_INCLUDED
