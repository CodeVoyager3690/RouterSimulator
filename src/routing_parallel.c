#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include "routing.h"
#include "helpers.h"
#include "packet.h"


void start_routing_parallel(int n_router, Router **routers) { 
    for (int i = 0; i < n_router; i++) {
        pthread_t thread;
        pthread_create(&thread, NULL, process_packets_parallel, (void *) routers[i]);
    }
}