#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

/*
int pthread_create(pthread_t *thread, const pthread_attr_t *attr,
                   void *(*start_routine) (void *), void *arg);
*/

pthread_mutex_t lock;

void* add(void* x){
    int* x_int = (int*) x;
    int i = -1;
    while((i = (i+1)) < 100000){    
        pthread_mutex_lock(&lock); 
        *x_int = *x_int + 1; 
        pthread_mutex_unlock(&lock);
    }
}


int main()
{
    pthread_t t1, t2;
    int z = 0; 
    pthread_mutex_init(&lock, NULL);
    pthread_create(&t1, NULL, add, &z);
    pthread_create(&t2, NULL, add, &z);
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    pthread_mutex_destroy(&lock);

    printf("final value z: %d", z);
    return 0;
}