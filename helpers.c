#include "helpers.h"
#include <stdlib.h>
#include <stdio.h>
void print_ip(uint32_t ip)
{
    int leftOctet = ip >> 24;
    int leftMiddleOctet = (ip >> 16) & 0xff;
    int rightMiddleOctet = (ip >> 8) & 0xff;
    int rightOctet = ip & 0xff;
    printf("%d.%d.%d.%d", leftOctet, leftMiddleOctet, rightMiddleOctet, rightOctet);
}

// circular queue
struct Queue
{
    size_t capacity;
    size_t rear; // enqueue position
    size_t head; // dequeue position
    Packet **packets;
};

Queue *create_queue(size_t capacity)
{
    Queue *q = malloc(sizeof(Queue));
    if (!q)
    {
        return NULL;
    }
    q->capacity = capacity;
    q->rear = 0;
    q->head = 0;
    q->packets = calloc(capacity, sizeof(Packet *));
    if (!q->packets)
    {
        return NULL;
    }
    return q;
}

void free_queue(Queue *q)
{
    if (!q)
    {
        return;
    }
    /*
    //if we want to free the packets
    for (int i = q->head; i != q->rear; i = ((i + 1) % q->capacity))
    {
        free_packet(q->packets[i]);
    }*/
    free(q->packets);
    free(q);
}

int is_empty_queue(Queue *q)
{
    return q->rear == q->head;
}

int is_full_queue(Queue *q)
{
    return ((q->rear + 1) % q->capacity) == q->head;
}
Packet *dequeue(Queue *q)
{
    if (q == NULL || is_empty_queue(q))
    {
        return NULL;
    }
    Packet *pck = q->packets[q->head];
    q->head = (q->head + 1) % q->capacity;
    return pck;
}
int enqueue(Queue *q, Packet *p)
{
    if (q == NULL || is_full_queue(q))
    {
        return 0;
    }
    q->packets[q->rear] = p;
    q->rear = (q->rear + 1) % q->capacity;
    return 1;
}

/*
int main()
{
    printf("helpers.c ran\n");
    return 0;
}*/