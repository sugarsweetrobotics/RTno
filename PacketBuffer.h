#ifndef PACKET_BUFFER_HEADER_INCLUDED
#define PACKET_BUFFER_HEADER_INCLUDED


void PacketBuffer_init(uint8_t size);

void PacketBuffer_clear();
void PacketBuffer_seek(uint8_t forward);
void PacketBuffer_seal();

void PacketBuffer_setInterface(int8_t interface_c);
int8_t PacketBuffer_getInterface();

void PacketBuffer_setAddress(int8_t* address);
int8_t* PacketBuffer_getAddress();

void PacketBuffer_setTargetPortIndex(int8_t index);
void PacketBuffer_setSourcePortIndex(int8_t index);

int8_t PacketBuffer_getTargetPortIndex();
int8_t PacketBuffer_getSourcePortIndex();

void PacketBuffer_push(const int8_t* src, uint8_t size);

uint8_t PacketBuffer_getReceivedPacketSize();
uint8_t PacketBuffer_getPacketSize();
int8_t* PacketBuffer_getBuffer();

int8_t PacketBuffer_getInterface();

int8_t* PacketBuffer_getDataBuffer();

int8_t PacketBuffer_getc(uint8_t index);
uint8_t PacketBuffer_get(uint8_t start, uint8_t stop, int8_t* dst);

#endif PACKET_BUFFER_HEADER_INCLUDED
