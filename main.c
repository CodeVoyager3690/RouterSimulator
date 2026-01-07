#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "routing.h"
#include "helpers.h"
#include "packet.h"
#include "routing_parallel.h"
#include "read_router_from_file.h"

#define ROUTES_FILE_NAME  "routes2.txt"
#define PACKETS_FILE_NAME "packets.txt"

int main(){
    RouterInfo* rinfo = read_routers_from_file(ROUTES_FILE_NAME);

    if (rinfo == NULL) {
        printf("Failed to read router info\n");
        return 1;
    }
    //print routing tables
    /*for (int i = 0; i < rinfo->nRouters; i++) {
        printf("Router ID: %llu\n", rinfo->routers[i]->ID);
        print_routing_table(rinfo->routers[i]->table);
    }*/
    
    FILE *fp = fopen(PACKETS_FILE_NAME, "w");
    if (fp != NULL) {
        fclose(fp);
    }
    start_routing_parallel(rinfo->nRouters, rinfo->routers);
    

    //create one packet and send to router with id 1
    uint8_t content[] = {'h', 'e', 'l', 'l', 'o', '\0'};
    Packet *p = create_packet(create_ip(10,11,12,13), create_ip(192,168,4,50),   64, content, 6);
    send_to_router(get_router_by_id(rinfo, 1), p);
    
    
    /*
    get packets from userinput
    input: source ip, destination ip, content, routerid to send packet to
    create packet and send to router with routerid
     */
    printf("\nEnter packet details (or 'q' to quit):\n");
    char input[256];
    while (1) {
        //--------------------get src ip address from input------
        printf("\nSource IP (a.b.c.d): ");
        if (fgets(input, sizeof(input), stdin) == NULL || input[0] == 'q')
        {
            break;
        }
        int src_ip_octet1, src_ip_octet2, src_ip_octet3, src_ip_octet4;
        //sscanf to get 4 octets
        //invalid input -> continue
        if (sscanf(input, "%d.%d.%d.%d", &src_ip_octet1, &src_ip_octet2, &src_ip_octet3, &src_ip_octet4) != 4) {
            printf("Invalid IP format\n");
            continue;
        }

        //----------------get dst ip address from input-----------
        printf("Destination IP (a.b.c.d): ");
        if (fgets(input, sizeof(input), stdin) == NULL || input[0] == 'q') 
        {
            break;
        }
        
        int dst_ip_octet1, dst_ip_octet2, dst_ip_octet3, dst_ip_octet4;
        //invalid input -> continue
        if (sscanf(input, "%d.%d.%d.%d", &dst_ip_octet1, &dst_ip_octet2, &dst_ip_octet3, &dst_ip_octet4) != 4) {
            printf("Invalid IP format\n");
            continue;
        }
        
        //---------------------get content from input-------------
        printf("Content: ");
        if (fgets(input, sizeof(input), stdin) == NULL || input[0] == 'q') break;
        //put input to an array of uint8_t
        //remove newline character from content if present (we don't want to print the newline in the output later)
        for (int i = 0; i < strlen(input); i++) {
            if (input[i] == '\n') {
                input[i] = '\0';
                break;
            }
        }
        int content_len = strlen(input) + 1;
        uint8_t *pkt_content = (uint8_t*)malloc(content_len * sizeof(uint8_t));
        strcpy((char*)pkt_content, input);
        
        
        
        //---------------------get router id from input-------------
        printf("Router ID to send to: ");
        int router_id;
        //invalid input -> continue
        if (scanf("%d", &router_id) != 1) { 
            printf("Invalid router ID\n");
            while(getchar() != '\n'); // Clear leftover input buffer
            continue;
        }

        while(getchar() != '\n'); // Clear input buffer

        //---------------received all input, now create and send packet to router-------
        Router *target_router = get_router_by_id(rinfo, router_id);
        if (target_router == NULL) {
            printf("Invalid router ID. Valid IDs: "); 
            for (int i = 0; i < rinfo->nRouters; i++) {
                if (rinfo->routers[i] != NULL) {
                    printf("%llu ", rinfo->routers[i]->ID);
                }
            }
            printf("\n");
            continue;
        }
        

        Packet *new_pkt = create_packet(
            create_ip(src_ip_octet1, src_ip_octet2, src_ip_octet3, src_ip_octet4),
            create_ip(dst_ip_octet1, dst_ip_octet2, dst_ip_octet3, dst_ip_octet4),
             64, pkt_content, content_len);
        send_to_router(target_router, new_pkt);
        printf("Packet sent to router %d\n", router_id);
        free(pkt_content); //create_packet makes its own copy of content
    }

   
    printf("SIMULATION FINISHED");
    free_router_info(rinfo);

    return 0;
}