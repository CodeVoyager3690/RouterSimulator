#ifndef PACKET_H
#define PACKET_H

#include <stdint.h>

#define PACKET_SERIALIZED_MIN_SIZE 10
//when serialized, a packet has at least 10 bytes: 4 for src, 4 for dest, 1 for ttl, 1 for content_len, (then content_len bytes for content)

typedef struct
{
    uint32_t src_address;
    uint32_t dest_address;
    uint8_t ttl;
    uint8_t content_len;
    uint8_t *content;
} Packet;

Packet *create_packet(uint32_t src, uint32_t dest, uint8_t ttl, uint8_t *content, uint8_t content_len);
void free_packet(Packet *p);
void print_packet(Packet *p);
uint8_t *serialize(Packet *pck);
Packet *deserialize(uint8_t *byte_arr);

#endif
