#include "helpers.h"
#include "routing.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>


Router *create_router(uint64_t id)
{
    Router *r = (Router *)malloc(sizeof(Router));
    if (!r)
    {
        exit(1);
    }
    r->ID = id;
    Queue *q = create_queue(1000);
    if (!q)
    {
        exit(1);
    }
    r->queue = q;
    r->table = (RoutingTable *)malloc(sizeof(RoutingTable));
    if (!r->table)
    {
        exit(1);
    }
    r->table->routeEntries = NULL;
    return r;
}

//initialize router with one route
Router *initialize_router(uint64_t id, uint32_t default_network, uint32_t default_mask, Router *default_next_hop)
{
    Router *r = create_router(id);
    
    // Create routing table
    RoutingTable *table = (RoutingTable *)malloc(sizeof(RoutingTable));
    if (!table)
    {
        exit(1);
    }
    
    // Create default route entry
    RouteEntry *default_entry = (RouteEntry *)malloc(sizeof(RouteEntry));
    if (!default_entry)
    {
        exit(1);
    }
    
    default_entry->destination_ip = default_network;
    default_entry->mask = default_mask;
    default_entry->nextHopRouter = default_next_hop;
    default_entry->next = NULL;
    
    table->routeEntries = default_entry;
    r->table = table;
    
    return r;
}

void add_route(Router *r, uint32_t destination_ip, uint32_t mask, Router *next_hop)
{
    if (r == NULL || r->table == NULL)
    {
        return;
    }
    
    // Create new route entry
    RouteEntry *new_entry = (RouteEntry *)malloc(sizeof(RouteEntry));
    if (!new_entry)
    {
        exit(1);
    }
    
    new_entry->destination_ip = destination_ip;
    new_entry->mask = mask;
    new_entry->nextHopRouter = next_hop;
    new_entry->next = NULL;
    
    // Add to the end of the linked list
    RouteEntry *current = r->table->routeEntries;
    if (current == NULL)
    {
        r->table->routeEntries = new_entry;
        return;
    }
    while (current->next != NULL)
    {
        current = current->next;
    }
    current->next = new_entry;
}



void send_to_router(Router *r, Packet *p)
{
    enqueue(r->queue, p);
}

void process_packet(Router *r){
    //printf("called");
    if (r == NULL || r->table == NULL)
    {
        return;
    }
    if(is_empty_queue(r->queue)){
        return; 
    }
    Packet *p = dequeue(r->queue);
    if (p == NULL)
    {
        return;
    }
    
  
    FILE *fp = fopen("packets.txt", "a");
    printf("-----PACKET %u ROUTER: %llu\n", p->dest_address, r->ID);
    if (fp != NULL) {
        fprintf(fp, "PACKET SRC: %u DEST: %u, CONTENT: %s ROUTER: %llu", p->src_address, p->dest_address, (char*)p->content, r->ID);
    }


    RouteEntry *best = NULL;
    int best_prefix = -1;

    // Find longest prefix match
    for (RouteEntry *entry = r->table->routeEntries; entry != NULL; entry = entry->next)
    {
        if (is_match(p, entry))
        {
            int prefix_len = __builtin_popcount(entry->mask);
            if (prefix_len > best_prefix)
            {
                best_prefix = prefix_len;
                best = entry;
            }
        }
    }

    if (best != NULL)
    {
        printf("Routing packet with dest ");
        print_ip(p->dest_address);
        if (best->nextHopRouter != NULL)
        {
            printf(" -> sending to router %llu\n", best->nextHopRouter->ID);
            fprintf(fp, "\n");
            fclose(fp);
            send_to_router(best->nextHopRouter, p);
            return; 
        }
        else
        {
            /* directly delivered locally */
            printf(" -> DIRECTLY DELIVERED TO ROUTER %llu\n", r->ID);
            fprintf(fp, " ARRIVED\n");
            fclose(fp);
            free_packet(p);
            return;
        }
    }
    else
    {
        printf("No route found. Dropping packet\n");
        fprintf(fp, " DROPPED\n");
        fclose(fp);
        free_packet(p);
        return;
    }
    ;
}


void process_packets(Router *r)
{
    if (r == NULL || r->table == NULL)
    {
        return;
    }

    while (!is_empty_queue(r->queue))
    {
        process_packet(r);
    }
}

void* process_packets_parallel(void *arg)
{
    Router *r = (Router *)arg;
    if (r == NULL || r->table == NULL)
    {
        return NULL;
    }

    while (1)
    {
        process_packet(r);
    }
    //return NULL;
}

int is_match(Packet *pck, RouteEntry *routeEntry)
{
    return (pck->dest_address & routeEntry->mask) == (routeEntry->destination_ip & routeEntry->mask);
}

void free_route_entries(RouteEntry *entry)
{
    while (entry != NULL)
    {
        RouteEntry *next = entry->next;
        free(entry);
        entry = next;
    }
}

void free_router(Router *r)
{
    if (r == NULL)
    {
        return;
    }
    
    // Free routing table and its entries
    if (r->table != NULL)
    {
        if (r->table->routeEntries != NULL)
        {
            free_route_entries(r->table->routeEntries);
        }
        free(r->table);
    }
    
    // Free queue (note: this will NOT free packets still in queue)
    if (r->queue != NULL)
    {
        free_queue(r->queue);
    }
    
    free(r);
}


/*
int main()
{
    printf("called routing.c");
    return 0;
}*/