#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include "routing.h"
#include "helpers.h"
#include "packet.h"


void* thread_function(void* arg) {
    int* num = (int*)arg;
    for(int i = 0; i < 10000; i++){
        (*num)++;
    }
    return NULL; // Or any pointer
}

int main(){ 
    int n_threads = 20; 
    pthread_t threads[20];
    int value = 42;

    for(int i = 0;i < n_threads; i++){
        if (pthread_create(&threads[i], NULL, thread_function, &value) != 0) {
        perror("Failed to create thread");
        return 1;
    }
}


    for(int i = 0; i < n_threads; i ++){
         pthread_join(threads[i], NULL);
    }    
    printf("value is %d", value);

  

    return 0;
}