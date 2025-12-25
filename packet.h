#ifndef PACKET_H
#define PACKET_H

#include <stdint.h>

#define MIN_PACKET_SIZE 10

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
