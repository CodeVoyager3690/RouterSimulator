#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

uint8_t *create_mac(uint8_t a, uint8_t b, uint8_t c, uint8_t d, uint8_t e, uint8_t f)
{
    uint8_t *out = malloc(6 * sizeof(uint8_t));
    out[0] = a;
    out[1] = b;
    out[2] = c;
    out[3] = d;
    out[4] = e;
    out[5] = f;
    return out;
}

/**
 * assumes big endiannes!
 */
uint64_t convert_to_uint46_t(uint8_t *mac)
{
    return mac[0] << (5 * 8) |
           mac[1] << (4 * 8) |
           mac[2] << (3 * 8) |
           mac[3] << (2 * 8) |
           mac[4] << 8 |
           mac[5];
}

int modulo(uint8_t *mac, int n)
{
    return convert_to_uint46_t(mac) % n;
}

int main()
{
    uint8_t *mac = create_mac(0x00, 0x00, 0x00, 0x00, 0x00, 0x01);

    // unsafe! assume
    u_int64_t macAsint = *((uint64_t *)mac);

    printf("%llu", macAsint);

    return 0;
}