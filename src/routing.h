#ifndef ROUTING_H
#define ROUTING_H

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include "helpers.h"

#define DEFAULT_ROUTER_QUEUE_SIZE 1000
typedef struct Router Router;

typedef struct RouteEntry
{
    uint32_t destination_ip; // network address (IPv4)
    uint32_t mask;           // subnet mask
    Router *nextHopRouter;   // to which router to send (next hop)
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
Router *initialize_router(uint64_t id, uint32_t default_network, uint32_t default_mask, Router *default_next_hop);
void add_route(Router *r, uint32_t destination_ip, uint32_t mask, Router *next_hop);
void send_to_router(Router *r, Packet *p);
void process_packets(Router *r);
void process_packet(Router *r);
int is_match(Packet *pck, RouteEntry *routeEntry);
void* process_packets_parallel(void *arg);
void free_route_entries(RouteEntry *entry);
void free_router(Router *r);

#endif
