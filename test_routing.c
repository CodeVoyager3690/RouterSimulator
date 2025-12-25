#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "routing.h"
#include "helpers.h"

void test_print_routing_table()
{
    printf("Test: print_routing_table\n");
    
    RouteEntry *entry3 = malloc(sizeof(RouteEntry));
    entry3->destination_ip = 0xC0A80300;  // 192.168.3.0
    entry3->mask = 0xFFFFFF00;
    entry3->next_hop_ip = 0xC0A80101;    // 192.168.1.1
    entry3->interface_id = 3;
    entry3->next = NULL;
    
    RouteEntry *entry2 = malloc(sizeof(RouteEntry));
    entry2->destination_ip = 0xC0A80200;  // 192.168.2.0
    entry2->mask = 0xFFFFFF00;
    entry2->next_hop_ip = 0xC0A80101;
    entry2->interface_id = 2;
    entry2->next = entry3;
    
    RouteEntry *entry1 = malloc(sizeof(RouteEntry));
    entry1->destination_ip = 0xC0A80100;  // 192.168.1.0
    entry1->mask = 0xFFFFFF00;
    entry1->next_hop_ip = 0x00000000;
    entry1->interface_id = 1;
    entry1->next = entry2;
    
    RoutingTable table;
    table.routeEntries = entry1;
    
    print_routing_table(&table);
    
    free(entry1);
    free(entry2);
    free(entry3);
    printf("Test passed\n\n");
}

void test_print_route_entry()
{
    printf("Test: print_route_entry\n");
    
    RouteEntry entry;
    entry.destination_ip = 0x0A000000;    // 10.0.0.0
    entry.mask = 0xFF000000;
    entry.next_hop_ip = 0xC0A80101;       // 192.168.1.1
    entry.interface_id = 5;
    
    print_route_entry(&entry);
    printf("Test passed\n\n");
}

int main()
{
    printf("=== Routing Tests ===\n\n");
    test_print_route_entry();
    test_print_routing_table();
    printf("All tests completed\n");
    return 0;
}