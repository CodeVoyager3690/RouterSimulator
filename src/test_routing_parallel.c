#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include "routing.h"
#include "helpers.h"
#include "packet.h"


int main(){ 
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

    // Create a packet destined to router 3
    uint8_t content[] = {'h', 'e', 'l', 'l', 'o', '\0'};
    int content_size = 6;
    uint32_t src_address = create_ip(10, 11, 12, 13);
    uint32_t dest_address = create_ip(192, 168, 4, 50);
    Packet *p = create_packet(src_address, dest_address, 64, content, content_size);    
    printf("Sending packet from ");
    print_ip(src_address);
    printf(" to ");
    print_ip(dest_address);
    printf("\nsending to router 1\n");
    printf("_______________________________\n");
    // Send packet to Router 1
    send_to_router(router1, p);

    pthread_t t1,t2,t3,t4; 
    pthread_create(&t1, NULL, process_packets_parallel, router1);
    pthread_create(&t2, NULL, process_packets_parallel, router2);
    pthread_create(&t3, NULL, process_packets_parallel, router3);
    pthread_create(&t4, NULL, process_packets_parallel, router4);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    pthread_join(t3, NULL);
    pthread_join(t4, NULL);
  

    free_router(router1);
    free_router(router2);
    free_router(router3);
    free_router(router4);

    return 0;
}