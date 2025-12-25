#include "helpers.h"
#include "routing.h"
#include <stdlib.h>
#include <stdio.h>

void print_routing_table(RoutingTable *table)
{
    RouteEntry *entry = table->routeEntries;
    printf("destination_ip\tmask\tnext_hop_ip\tinterface_id\n");
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
    print_ip(r->next_hop_ip);
    printf("\t");
    printf("%d", r->interface_id);
    printf("\n");
}

/*
int main()
{
    printf("called routing.c");
    return 0;
}*/