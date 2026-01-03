#include "helpers.h" // for print_ip
#include <stdlib.h>
#include <stdio.h>

Packet *create_packet(uint32_t src, uint32_t dest, uint8_t ttl, uint8_t *content, uint8_t content_len)
{
    Packet *p = malloc(sizeof(Packet));
    if (!p)
    {
        exit(1);
    }
    p->src_address = src;
    p->dest_address = dest;
    p->ttl = ttl;
    p->content_len = content_len;
    p->content = malloc(content_len * sizeof(uint8_t));
    for (int i = 0; i < content_len; i++)
    {
        p->content[i] = content[i];
    }
    return p;
}

void free_packet(Packet *p)
{
    if (!p)
    {
        return;
    }
    free(p->content);
    free(p);
}

void print_packet(Packet *p)
{
    printf("src: ");
    print_ip(p->src_address);
    printf("\n");
    printf("dest: ");
    print_ip(p->dest_address);
    printf("\n");
    printf("TTL: %d", p->ttl);
    printf("\n");
    printf("content: ");
    for (int i = 0; i < p->content_len; i++)
    {
        printf("%c", p->content[i]); //(assuming content are chars)
    }
    printf("\n");
}

//big endian order for network
uint8_t *serialize(Packet *pck)
{
    uint8_t *out = calloc(MIN_PACKET_SIZE + pck->content_len, sizeof(uint8_t));
    if(!out){
        exit(1);
    }
    out[0] = pck->src_address >> 24;
    out[1] = (pck->src_address >> 16) & 0xff;
    out[2] = (pck->src_address >> 8) & 0xff;
    out[3] = pck->src_address & 0xff;

    out[4] = pck->dest_address >> 24;
    out[5] = (pck->dest_address >> 16) & 0xff;
    out[6] = (pck->dest_address >> 8) & 0xff;
    out[7] = pck->dest_address & 0xff;
    out[8] = pck->ttl;

    out[9] = pck->content_len;
    for (int i = 0; i < pck->content_len; i++)
    {
        out[10 + i] = pck->content[i];
    }

    return out;
}

Packet *deserialize(uint8_t *byte_arr)
{
    uint32_t src_address = ((uint32_t)byte_arr[0] << 24) | ((uint32_t)byte_arr[1] << 16) | ((uint32_t)byte_arr[2] << 8) | (uint32_t)byte_arr[3];
    uint32_t dest_address = ((uint32_t)byte_arr[4] << 24) | ((uint32_t)byte_arr[5] << 16) | ((uint32_t)byte_arr[6] << 8) | (uint32_t)byte_arr[7];
    uint8_t ttl = byte_arr[8];
    uint8_t content_len = byte_arr[9];
    uint8_t *content = &byte_arr[10];
    return create_packet(src_address, dest_address, ttl, content, content_len);
}

/*
int main()
{
    printf("packet.c ran \n");
    return 0;
}*/