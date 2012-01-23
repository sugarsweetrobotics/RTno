#ifndef SEQUENCE_HEADER_INCLUDED
#define SEQUENCE_HEADER_INCLUDED

class SequenceBase {
 protected:
    unsigned char m_length;

 public:
  unsigned char length() {
    return m_length;
  }

};


template<typename T>
class Sequence : public SequenceBase {
  T *m_ptr;

 public:
  Sequence() {m_ptr = 0;}
  void length(unsigned char len) {
    delete m_ptr;
    m_ptr = new T[len];
    this->m_length = len;
    //    free((void*)m_ptr); m_ptr = malloc(len * sizeof(T));
  }


  T& operator[](int index) {
    return m_ptr[index];
  }

  T* operator&() {
    return m_ptr;
  }
};


#endif //#ifndef SEQUENCE_HEADER_INCLUDED
