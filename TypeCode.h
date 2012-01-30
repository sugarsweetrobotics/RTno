#ifndef TYPECODE_HEADER_INCLUDED
#define TYPECODE_HEADER_INCLUDED

#include <stdint.h>
uint8_t TypeCode_isSequence(const char typeCode);

uint8_t TypeCode_getElementSize(const char typeCode);

#endif // #ifndef TYPECODE_HEADER_INCLUDED
