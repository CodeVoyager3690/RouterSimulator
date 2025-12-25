#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

typedef struct RouteEntry
{
    uint32_t destination_ip; // network address (IPv4)
    uint32_t mask;           // subnet mask
    uint32_t next_hop_ip;    // next-hop IP (0 if directly connected)
    int interface_id;        // which interface to use
    struct RouteEntry *next;
} RouteEntry;

typedef struct RoutingTable
{
    RouteEntry *routeEntries;
} RoutingTable;

typedef struct Router
{
    RoutingTable *table;
} Router;

void print_routing_table(RoutingTable *table);
void print_route_entry(RouteEntry *r);
