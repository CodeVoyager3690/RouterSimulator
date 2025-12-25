#ifndef HELPERS_H
#define HELPERS_H

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include "packet.h"

// IP printing
void print_ip(uint32_t ip);

// Circular queue
typedef struct Queue Queue;

Queue *create_queue(size_t capacity);
void free_queue(Queue *q);
int is_empty_queue(Queue *q);
int is_full_queue(Queue *q);
int enqueue(Queue *q, Packet *p);
Packet *dequeue(Queue *q);

#endif
