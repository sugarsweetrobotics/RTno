#ifndef PORT_PROFILE_HEADER_INCLUDED
#define PORT_PROFILE_HEADER_INCLUDED


#include "PortBase.h"

typedef struct _PortProfile {
public:
  int length;
  char* data;
}PortProfile;


PortProfile* PortProfile_create(const char* name, const char typeCode);
void PortProfile_destroy(PortProfile* pProfile);
#endif // #ifndef PORT_PROFILE_HEADER_INCLUDED
