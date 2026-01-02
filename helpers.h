#ifndef HELPERS_H
#define HELPERS_H

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include "packet.h"
// forward declarations to avoid circular includes
typedef struct RoutingTable RoutingTable;
typedef struct RouteEntry RouteEntry;

// IP printing
void print_ip(uint32_t ip);

// circular queue
typedef struct Queue
{
    size_t capacity;
    size_t rear; // enqueue position
    size_t head; // dequeue position
    Packet **packets;
} Queue;

Queue *create_queue(size_t capacity);
void free_queue(Queue *q);
int is_empty_queue(Queue *q);
int is_full_queue(Queue *q);
int enqueue(Queue *q, Packet *p);
Packet *dequeue(Queue *q);
void print_routing_table(RoutingTable *table);
void print_route_entry(RouteEntry *r);

#endif
