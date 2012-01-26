#include <ctype.h>

#include "TypeCode.h"

int TypeCode_isSequence(const char typeCode) {
  return isupper(typeCode);
}

int TypeCode_getElementSize(const char typeCode) {
  switch(tolower(typeCode)) {
  case 'b':
  case 'c':
  case 'o':
    return 1;
  case 'l':
  case 'f':
  case 'd': // double is 32 bit in arduino
    return 4;
  default:
    return 4;
  }
}
