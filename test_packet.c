#include "packet.h"
#include <stdio.h>
#include <stdlib.h>

int main()
{
    uint32_t src =
        (uint32_t)13 | ((uint32_t)12 << 8) | ((uint32_t)11 << 16) | ((uint32_t)10 << 24);

    uint32_t dest =
        (uint32_t)4 | ((uint32_t)3 << 8) | ((uint32_t)2 << 16) | ((uint32_t)1 << 24);

    uint8_t content[] = {'h', 'e', 'l', 'l', 'o'};
    Packet *p = create_packet(src, dest, 60, content, sizeof(content));

    uint8_t *byte_arr = serialize(p);
    Packet *copy = deserialize(byte_arr);
    copy->content[0] = 'H';

    printf("ORIGINAL:\n");
    print_packet(p);

    printf("COPY:\n");
    print_packet(copy);

    free_packet(p);
    free_packet(copy);
    free(byte_arr);

    return 0;
}