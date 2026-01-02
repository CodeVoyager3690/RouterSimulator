#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "routing.h"
#include "helpers.h"

void test_multi_hop_routing()
{
    printf("=== Test: Multi-Hop Router Network ===\n\n");

    // Create 4 routers in a chain
    Router *router1 = create_router(1);
    Router *router2 = create_router(2);
    Router *router3 = create_router(3);
    Router *router4 = create_router(4);

    printf("Created 4 routers with IDs: 1, 2, 3, 4\n\n");

    // Setup Router 1's routing table
    // Routes packets destined to 192.168.2.0/24 to Router 2
    RouteEntry r1_entry;
    r1_entry.destination_ip = 0xC0000000; // 192.0.0.0
    r1_entry.mask = 0xFF000000;           // 8
    r1_entry.router = router2;
    r1_entry.next = NULL;

    RoutingTable r1_table;
    r1_table.routeEntries = &r1_entry;
    router1->table = &r1_table;

    printf("Router 1: Routes 192.168.2.0/24 -> Router 2\n");

    // Setup Router 2's routing table
    // Routes packets destined to 192.168.3.0/24 to Router 3
    RouteEntry r2_entry;
    r2_entry.destination_ip = 0xC0A80000; // 192.168.0.0
    r2_entry.mask = 0xFFFF0000;           // 16
    r2_entry.router = router3;
    r2_entry.next = NULL;

    RoutingTable r2_table;
    r2_table.routeEntries = &r2_entry;
    router2->table = &r2_table;

    printf("Router 2: Routes 192.168.3.0/24 -> Router 3\n");

    // Setup Router 3's routing table
    // Routes packets destined to 192.168.4.0/24 to Router 4
    RouteEntry r3_entry;
    r3_entry.destination_ip = 0xC0A80400; // 192.168.4.0
    r3_entry.mask = 0xFFFFFF00;           // /24
    r3_entry.router = router4;
    r3_entry.next = NULL;

    RoutingTable r3_table;
    r3_table.routeEntries = &r3_entry;
    router3->table = &r3_table;

    printf("Router 3: Routes 192.168.4.0/24 -> Router 4\n\n");

    // Create a packet destined to 192.168.4.50 (in Router 4's subnet)
    uint8_t cnt[] = {'h', 'e', 'l', 'l', 'o'}; // 5 bytes
    Packet *p = create_packet(0xC0A80101, 0xC0A80432, 64, cnt, 5);

    printf("Sending packet from ");
    print_ip(p->src_address);
    printf(" to ");
    print_ip(p->dest_address);
    printf("\n\n");

    // Send packet to Router 1
    send_to_router(router1, p);
    printf("Packet queued at Router 1\n");

    // Process packets at Router 1
    printf("\n--- Router 1 Processing ---\n");
    process_packets(router1);

    // Check if packet reached Router 2
    if (!is_empty_queue(router2->queue))
    {
        printf("✓ Packet forwarded to Router 2\n");

        // Process packets at Router 2
        printf("\n--- Router 2 Processing ---\n");
        process_packets(router2);

        // Check if packet reached Router 3
        if (!is_empty_queue(router3->queue))
        {
            printf("✓ Packet forwarded to Router 3\n");

            // Process packets at Router 3
            printf("\n--- Router 3 Processing ---\n");
            process_packets(router3);

            // Check if packet reached Router 4
            if (!is_empty_queue(router4->queue))
            {
                printf("✓ Packet forwarded to Router 4\n");
                printf("\n✓✓✓ SUCCESS: Packet traversed all 4 routers correctly! ✓✓✓\n\n");
            }
            else
            {
                printf("✗ Packet did not reach Router 4\n");
            }
        }
        else
        {
            printf("✗ Packet did not reach Router 3\n");
        }
    }
    else
    {
        printf("✗ Packet did not reach Router 2\n");
    }
}

int main()
{
    printf("\n========================================\n");
    printf("  MULTI-HOP ROUTING SCENARIO TEST\n");
    printf("========================================\n\n");

    test_multi_hop_routing();

    printf("========================================\n");
    printf("  TEST COMPLETE\n");
    printf("========================================\n\n");

    return 0;
}
