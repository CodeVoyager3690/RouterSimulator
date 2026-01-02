#include "helpers.h"
#include "routing.h"
#include <stdlib.h>
#include <stdio.h>

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

    r->table = NULL;
    return r;
}

// todo add routin table and entries;

void send_to_router(Router *r, Packet *p)
{
    enqueue(r->queue, p);
}

void process_packets(Router *r)
{
    if (r == NULL || r->table == NULL)
    {
        return;
    }

    while (!is_empty_queue(r->queue))
    {
        Packet *p = dequeue(r->queue);
        if (p == NULL)
        {
            continue;
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
            if (best->router != NULL)
            {
                printf(" to router %llu\n", best->router->ID);
                /* forward: enqueue on next router's queue — do NOT free here */
                send_to_router(best->router, p);
                continue; /* packet now owned by next router */
            }
            else
            {
                /* directly delivered locally */
                printf(" directly delivered\n");
                free_packet(p);
                continue;
            }
        }
        else
        {
            printf("No route found. Dropping packet\n");
            free_packet(p);
            continue;
        }
    }
}

int is_match(Packet *pck, RouteEntry *routeEntry)
{
    return (pck->dest_address & routeEntry->mask) == (routeEntry->destination_ip & routeEntry->mask);
}

/*
int main()
{
    printf("called routing.c");
    return 0;
}*/