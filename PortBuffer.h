#ifndef PORT_BUFFER_HEADER_INCLUDED
#define PORT_BUFFER_HEADER_INCLUDED



#ifdef __cplusplus
extern "C" {
#endif

  struct _PortBuffer;

  typedef struct _PortBuffer PortBuffer;
  struct _PortBuffer {
    void(*push)(PortBuffer* _this, const char* data, int size);
    void(*pop)(PortBuffer* _this, char* data, int size);
    int(*getNextDataSize)(PortBuffer* _this);
    int(*hasNext)(PortBuffer *_this);
    void* privateData;
  };
  
#ifdef __cplusplus
}
#endif




#endif // #ifndef PORT_BUFFER_HEADER_INCLUDED
