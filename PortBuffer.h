#ifndef PORT_BUFFER_HEADER_INCLUDED
#define PORT_BUFFER_HEADER_INCLUDED



#ifdef __cplusplus
extern "C" {
#endif

  struct _PortBuffer;

  typedef struct _PortBuffer PortBuffer;
  struct _PortBuffer {
    void(*push)(PortBuffer* _this, const int8_t* data, uint8_t size);
    void(*pop)(PortBuffer* _this, int8_t* data, uint8_t size);
    uint8_t(*getNextDataSize)(PortBuffer* _this);
    uint8_t(*hasNext)(PortBuffer *_this);
    void* privateData;
  };
  
#ifdef __cplusplus
}
#endif




#endif // #ifndef PORT_BUFFER_HEADER_INCLUDED
