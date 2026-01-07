#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "routing.h"
#include "helpers.h"
#include "packet.h"
#include "read_router_from_file.h"


void free_router_info(RouterInfo* rinfo){
    for(int i = 0; i < rinfo->nRouters; i++){
        free_router(rinfo->routers[i]);
    }
    free(rinfo->routers);
    free(rinfo);
}

Router* get_router_by_id(RouterInfo* rinfo, int id){
    for(int i = 0; i < rinfo->nRouters; i++){
        if(rinfo->routers[i]->ID == id){
            return rinfo->routers[i];
        }
    }
    return NULL;
}


//assumes perfectly formatted file with no mistakes (like referencing id's that don't have a router associated with them)
RouterInfo* read_routers_from_file(const char *filename){
    FILE *fp = fopen(filename, "r");
    if (fp == NULL) {
        printf("Error: Could not open file %s\n", filename);
        return NULL;
    }
    
    int i = 0;    
    char ch;
    RouterInfo* rinfo = malloc(sizeof(RouterInfo));
    if (rinfo == NULL) {
        fclose(fp);
        return NULL;
    }
    
    rinfo->routers = calloc(MAX_ROUTERS, sizeof(Router*));
    if (rinfo->routers == NULL) {
        free(rinfo);
        fclose(fp);
        return NULL;
    }
    
    //Read router IDs from the first line
    while ((ch = fgetc(fp)) != EOF && ch != '\n') {
        if (ch >= '0' && ch <= '9') { //can only have 10 routers with id's from 0 to 9 
            int router_id = ch - '0';
            Router* r = create_router(router_id);
            rinfo->routers[i] = r;
            i++;
        } 
    }
    rinfo->nRouters = i;


    //read the routes. The routes are in the format:
    //<source_router_id> <destination_network> <subnet_mask> <next_hop_router_id>
    int router_id, next_hop_router_id;
    char ip[16], mask[16];  

    char line[128];
    while (fgets(line, sizeof(line), fp) != NULL) {
        if (sscanf(line, "%d %15s %15s %d", &router_id, ip, mask, &next_hop_router_id) == 4) {
            //add a route from router a to destination_network ip1 with subnet_mask ip2 via next_hop_router b
            uint32_t dest_network = ip_str_to_uint32(ip);
            uint32_t subnet_mask = ip_str_to_uint32(mask);
            Router *r = get_router_by_id(rinfo, router_id);
            Router *next_hop = next_hop_router_id == -1 ? NULL : get_router_by_id(rinfo, next_hop_router_id); //-1 indicates direct delivery
            add_route(r, dest_network, subnet_mask, next_hop); //add route to routing table of router r
        } else {
            printf("Parse error\n");
        }
    }
    fclose(fp);
    return rinfo;   
}