#ifndef PACKET_BUFFER_HEADER_INCLUDED
#define PACKET_BUFFER_HEADER_INCLUDED

void PacketBuffer_init(uint8_t size);
void PacketBuffer_setInterface(int8_t interface_c);
void PacketBuffer_putc(uint8_t index);
void PacketBuffer_set(uint8_t start, uint8_t stop, const int8_t* src);
uint8_t PacketBuffer_getDataLength();
int8_t PacketBuffer_getc(uint8_t index);
uint8_t PacketBuffer_get(uint8_t start, uint8_t stop, int8_t* dst);

#endif PACKET_BUFFER_HEADER_INCLUDED
