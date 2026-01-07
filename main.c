#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "routing.h"
#include "helpers.h"
#include "packet.h"
#include "routing_parallel.h"
#include "read_router_from_file.h"

int main(){
    char routes_file_name[] = "routes2.txt";
    RouterInfo* rinfo = read_routers_from_file(routes_file_name);

    if (rinfo == NULL) {
        printf("Failed to read router info\n");
        return 1;
    }
    //print routing tables
    /*for (int i = 0; i < rinfo->nRouters; i++) {
        printf("Router ID: %llu\n", rinfo->routers[i]->ID);
        print_routing_table(rinfo->routers[i]->table);
    }*/
    
    FILE *fp = fopen("packets.txt", "w");
    if (fp != NULL) {
        fclose(fp);
    }
    start_routing_parallel(rinfo->nRouters, rinfo->routers);
    
    uint8_t content[] = {'h', 'e', 'l', 'l', 'o', '\0'};
    Packet *p = create_packet(create_ip(10,11,12,13), create_ip(192,168,4,50),   64, content, 6);
    send_to_router(rinfo->routers[0], p);
    
    //get packets from userinput. puts in source ip, destination ip, content and first routerid to send to. create packet and send to router with router id
    printf("\nEnter packet details (or 'q' to quit):\n");
    char input[256];
    while (1) {
        printf("\nSource IP (a.b.c.d): ");
        if (fgets(input, sizeof(input), stdin) == NULL || input[0] == 'q')
        {
            break;
        }
        int sa, sb, sc, sd;
        if (sscanf(input, "%d.%d.%d.%d", &sa, &sb, &sc, &sd) != 4) {
            printf("Invalid IP format\n");
            continue;
        }
        
        printf("Destination IP (a.b.c.d): ");
        if (fgets(input, sizeof(input), stdin) == NULL || input[0] == 'q') 
        {
            break;
        }
        
        int da, db, dc, dd;
        if (sscanf(input, "%d.%d.%d.%d", &da, &db, &dc, &dd) != 4) {
            printf("Invalid IP format\n");
            continue;
        }
        
        printf("Content: ");
        if (fgets(input, sizeof(input), stdin) == NULL || input[0] == 'q') break;
        input[strcspn(input, "\n")] = '\0'; 
        
        printf("Router ID to send to: ");
        int router_id;
        if (scanf("%d", &router_id) != 1) {
            printf("Invalid router ID\n");
            while(getchar() != '\n'); // Clear input buffer
            continue;
        }
        while(getchar() != '\n'); // Clear input buffer
        
        Router *target_router = get_router_by_id(rinfo, router_id);
        if (target_router == NULL) {
            printf("Invalid router ID. Valid IDs: ");
            printf("yuuu");
            for (int i = 0; i < rinfo->nRouters; i++) {
                if (rinfo->routers[i] != NULL) {
                    printf("%llu ", rinfo->routers[i]->ID);
                }
            }
            printf("\n");
            continue;
        }
        
        uint8_t *pkt_content = (uint8_t*)malloc(strlen(input) + 1);
        strcpy((char*)pkt_content, input);
        
        Packet *new_p = create_packet(create_ip(sa, sb, sc, sd), create_ip(da, db, dc, dd), 64, pkt_content, strlen(input) + 1);
        send_to_router(target_router, new_p);
        printf("Packet sent to router %d\n", router_id);
        free(pkt_content);
    }

    // To let the simulation run 
    //sleep(2);
    
   
    printf("SIMULATION FINISHED");
    free_router_info(rinfo);

    return 0;
}