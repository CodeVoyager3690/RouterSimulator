#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "routing.h"
#include "helpers.h"

void test_multi_hop_routing()
{
    printf("=== Test: Multi-Hop Router Network ===\n\n");

    // Create 4 routers with routing tables initialized
    Router *router1 = initialize_router(1, create_ip(192, 0, 0, 0), 0xFF000000, NULL);
    Router *router2 = initialize_router(2, create_ip(192, 168, 0, 0), 0xFFFF0000, NULL);
    Router *router3 = initialize_router(3, create_ip(192, 168, 4, 0), 0xFFFFFF00, NULL);
    Router *router4 = initialize_router(4, create_ip(192, 168, 4, 50), 0xFF000000, NULL);

    printf("Created 4 routers with IDs: 1, 2, 3, 4\n\n");

    // Setup routing for Router 1
    router1->table->routeEntries->nextHopRouter = router2;
    printf("Router 1: Routes 192.0.0.0/8 -> Router 2\n");

    // Setup routing for Router 2
    router2->table->routeEntries->nextHopRouter = router3;
    printf("Router 2: Routes 192.168.0.0/16 -> Router 3\n");

    // Setup routing for Router 3
    router3->table->routeEntries->nextHopRouter = router4;
    printf("Router 3: Routes 192.168.4.0/24 -> Router 4\n\n");

    // Create a packet destined to 192.168.4.50
    uint8_t content[] = {'h', 'e', 'l', 'l', 'o', '\0'};
    int content_size = 6;
    uint32_t src_address = create_ip(10, 11, 12, 13);
    uint32_t dest_address = create_ip(192, 168, 4, 50);
    Packet *p = create_packet(src_address, dest_address, 64, content, content_size);

    printf("Sending packet from ");
    print_ip(src_address);
    printf(" to ");
    print_ip(dest_address);
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

                // Process packets at Router 4
                printf("\n--- Router 4 Processing ---\n");
                process_packets(router4);

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
    
    // Cleanup
    free_router(router1);
    free_router(router2);
    free_router(router3);
    free_router(router4);
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
