#ifndef NULL_BUFFER_HEADER_INCLUDED
#define NULL_BUFFER_HEADER_INCLUDED

#include "PortBuffer.h"

PortBuffer* NullBuffer_create();
void NullBuffer_destroy(PortBuffer* _this);

#endif
