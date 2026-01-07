#include <stdio.h>
#include <stdint.h>
#include <arpa/inet.h>
#include <errno.h>
#include <string.h>

int main(void)
{
    const char *ip_str = "192.168.1.10";
    struct in_addr addr;

    int ret = inet_pton(AF_INET, ip_str, &addr);

    if (ret == 1) {
        // addr.s_addr is in network byte order (big-endian)
        uint32_t ip_net  = addr.s_addr;
        uint32_t ip_host = ntohl(addr.s_addr);

        printf("IP string : %s\n", ip_str);
        printf("Network order: 0x%08X\n", ip_net);
        printf("Host order   : 0x%08X\n", ip_host);
    }
    else if (ret == 0) {
        printf("Invalid IP address string: %s\n", ip_str);
    }
    else { // ret == -1
        perror("inet_pton failed");
    }

    printf("%d\n", strcspn("hallo", "a"));

    return 0;
}
