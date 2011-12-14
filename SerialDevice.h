#ifndef SERIAL_DEVICE_HEADER_INCLUDED
#define SERIAL_DEVICE_HEADER_INCLUDED

class SerialDevice {
	
	
private:


public:
	/**
	 * Write Specific Byte Data.
	 */
	virtual void write(const void* data, int size) = 0;
	
	/**
	 * Return Received Buffer Size.
	 */
	virtual int available() = 0;
	
	/**
	 * Read One Byte.
	 */
	virtual int read() = 0;
};

#endif
