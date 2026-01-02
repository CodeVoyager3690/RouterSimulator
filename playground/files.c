#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
int main(int argc, char *argv[]){
    if(argc != 3){
        fprintf(stderr, "Usage: %s <input_file> <output_file>\n", argv[0]);
        return EXIT_FAILURE;
    }
    
    FILE* fsource = fopen(argv[1], "r");
    FILE* fdest = fopen(argv[2], "w");
    if(fsource == NULL || fdest == NULL){
        perror("Error opening file");
        return EXIT_FAILURE;
   
    }
    // copy contents from source to destination in reverse order. First clear the destination file.
    //fseek(fdest, 0, SEEK_SET);
    fseek(fsource, 0, SEEK_END);
    long filesize = ftell(fsource);
    for(long i = filesize - 1; i >= 0; i--){
        fseek(fsource, i, SEEK_SET);
        int ch = fgetc(fsource);
        fputc(ch, fdest);
    }
    fclose(fsource);
    fclose(fdest);
   
    return 0;
}