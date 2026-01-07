#include <stdio.h>
#include <stdlib.h>
#include <string.h> 
#include <errno.h>
#include <unistd.h>

int main(){

   for(int i = 0; i < 10; i++){
       pid_t pid = fork();
       char seed[] ={i + '0', '\0'}; // Convert int to string
       if(pid < 0){
           perror("Fork failed");
           exit(1);
       } else if(pid == 0){
           // Child process
          if(execlp("./forProcesses", "./forProcesses", seed, NULL)==-1){
              fprintf(stderr, "execl error: %s\n", strerror(errno));
             return 1;
          }
       } 
   }
    return 0;
}