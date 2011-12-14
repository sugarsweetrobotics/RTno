#ifndef PORT_BUFFER_HEADER_INCLUDED
#define PORT_BUFFER_HEADER_INCLUDED



class PortBuffer {
private:


public:
	virtual void push(const char* data, int size) = 0;
	virtual void pop(char* data, int size) = 0;
	virtual int getNextDataSize() = 0;
	virtual int hasNext() = 0;
};

#endif // #ifndef PORT_BUFFER_HEADER_INCLUDED
