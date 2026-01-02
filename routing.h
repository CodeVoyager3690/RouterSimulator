#ifndef ROUTING_H
#define ROUTING_H

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include "helpers.h"

typedef struct Router Router;

typedef struct RouteEntry
{
    uint32_t destination_ip; // network address (IPv4)
    uint32_t mask;           // subnet mask
    Router *router;          // to which router to send (next hop)
    struct RouteEntry *next;
} RouteEntry;

typedef struct RoutingTable
{
    RouteEntry *routeEntries;
} RoutingTable;

typedef struct Router
{
    Queue *queue;
    uint64_t ID;
    RoutingTable *table;
} Router;

void print_routing_table(RoutingTable *table);
void print_route_entry(RouteEntry *r);
Router *create_router(uint64_t ip);
void send_to_router(Router *r, Packet *p);
void process_packets(Router *r);
int is_match(Packet *pck, RouteEntry *routeEntry);

#endif
