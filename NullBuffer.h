#ifndef NULL_BUFFER_HEADER_INCLUDED
#define NULL_BUFFER_HEADER_INCLUDED

#include "PortBuffer.h"

class NullBuffer : public PortBuffer {
private:
	char* m_pData;
	int m_Size;
	int isUpdated;
public:
	NullBuffer();
	virtual ~NullBuffer();

	void push(const char* pData, int size);
	void pop(char* pData, int size);
	int getNextDataSize();
	int hasNext();
};


#endif
