#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>

int main(){
    printf("hello world");
    system("echo hello world");
    printf("yo\n");
    printf("User: %s\n", getenv("USER"));
    printf("LANG: %s\n", getenv("LANG"));
    execlp("hduezfdhzeuifhiuzefz", "whahaa");
    fprintf(stderr,"%s",strerror(errno));
    if(!NULL){
        printf("not null\n");
    }
    return 0;
}