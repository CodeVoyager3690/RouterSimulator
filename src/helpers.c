#include "helpers.h"
#include "routing.h"
#include <stdlib.h>
#include <stdio.h>

void print_routing_table(RoutingTable *table)
{
    RouteEntry *entry = table->routeEntries;
    printf("destination_ip\tmask\tnext_hop_router\n");
    while (entry != NULL)
    {
        print_route_entry(entry);
        entry = entry->next;
    }
}
void print_route_entry(RouteEntry *r)
{

    print_ip(r->destination_ip);
    printf("\t");
    print_ip(r->mask);
    printf("\t");
    if (r->nextHopRouter != NULL)
    {
        printf("router-%llu", r->nextHopRouter->ID);
    }
    else
    {
        printf("direct");
    }
    printf("\n");
}
void print_ip(uint32_t ip)
{
    int leftOctet = ip >> 24;
    int leftMiddleOctet = (ip >> 16) & 0xff;
    int rightMiddleOctet = (ip >> 8) & 0xff;
    int rightOctet = ip & 0xff;
    printf("%d.%d.%d.%d", leftOctet, leftMiddleOctet, rightMiddleOctet, rightOctet);
}

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
        exit(1);
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
    return ((q->rear + 1) % q->capacity) == q->head; //one entry is "wasted" to make the difference with an empty queue
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

uint32_t create_ip(uint32_t octet1,uint32_t octet2, uint32_t octet3, uint32_t octet4){
    return octet1 << 24 | octet2 << 16 | octet3 << 8 | octet4;
}

//there exists  also the built in function int inet_pton(int af, const char *src, void *dst);
void ip_to_string(uint32_t ip, char *buffer){
    int octet1 = (ip >> 24) & 0xFF;
    int octet2 = (ip >> 16) & 0xFF;
    int octet3 = (ip >> 8) & 0xFF;
    int octet4 = ip & 0xFF;
    sprintf(buffer, "%d.%d.%d.%d", octet1, octet2, octet3, octet4);
}

uint32_t ip_str_to_uint32(char* ip_str){
    uint32_t ip = 0;
    char *p = ip_str; 
    int octet = 0; 
    int leftShift = 24;
    while(1){
        if(*p == '.' || *p == '\0'){
            ip = ip | (octet << leftShift);
            leftShift -= 8; 
            octet = 0;
            if(*p == '\0'){
                break;
            }
        }
        else {
            int d = *p - '0';
            octet = octet * 10 + d;
        }
        p++;
    }
    return ip;
}