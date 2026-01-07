
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
//write code that appends a random number to a file named "result.txt"
int main(int arg, char* argv[]){
    FILE *file = fopen("result.txt", "a");
    if (file == NULL) {
        perror("Error opening file");
        return 1;
    }
    //get seed as command line argument
    int seed = argv[1] ? atoi(argv[1]) : 0;
    srand(seed);
    int random_number = rand();
    fprintf(file, "%d\n", random_number);
    fclose(file);
    return 0;
}
