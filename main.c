#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
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
    // clear output file
    FILE *fp = fopen("output.txt", "w");
    if (fp != NULL) {
        fclose(fp);
    }
    fp = fopen("output.txt", "a");
    if (fp != NULL) {
        fprintf(fp, "Simulation started with %d routers\n", rinfo->nRouters);
        fclose(fp);
    }
    
    //clear packets file
    fp = fopen("packets.txt", "w");
    if (fp != NULL) {
        fclose(fp);
    }
    start_routing_parallel(rinfo->nRouters, rinfo->routers);
    
    uint8_t content[] = {'h', 'e', 'l', 'l', 'o', '\0'};
    Packet *p = create_packet(create_ip(10,11,12,13), create_ip(192,168,4,50),   64, content, 6);
    send_to_router(rinfo->routers[0], p);
    
    // Let the simulation run for a while
    sleep(2);
    
    fp = fopen("output.txt", "a");
    if (fp != NULL) {
        fprintf(fp, "Simulation ended\n");
        fclose(fp);
    }

    return 0;
}