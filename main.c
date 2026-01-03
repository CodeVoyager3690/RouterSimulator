#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "routing.h"
#include "helpers.h"
#include "packet.h"
#include "routing_parallel.h"
#include "read_router_from_file.h"

int main() {
    RouterInfo* rinfo = read_routers_from_file("routes.txt");
    if (rinfo == NULL) {
        printf("Failed to read router info\n");
        return 1;
    }
    for (int i = 0; i < rinfo->nRouters; i++) {
        printf("Router ID: %llu\n", rinfo->routers[i]->ID);
        print_routing_table(rinfo->routers[i]->table);
    }

    FILE *fp = fopen("output.txt", "a");
    fprintf(fp, "Simulation started with %d routers\n", rinfo->nRouters);
    start_routing_parallel(rinfo->nRouters, rinfo->routers);
    fclose(fp);

    return 0;
}