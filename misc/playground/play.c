#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#define SIZE 3
typedef int vast_matrix[SIZE][SIZE];

struct rec{
    int a[4];
    size_t i; 
    struct rec *next;
};

typedef struct{
    int a;
    char b; 
} Example;

void loop(struct rec* inputRec){
    struct rec* current = inputRec;
    while(current != NULL){
        printf("%zu", current->i),
        current = current->next;
    }
}

void test(){
    static int x;
    printf("static x: %d\n", x); 
    x++;
}

#define M 3
#define N 2
void loop_2d_array(int input[M][N]){
    for(int i = 0; i < M; i++){
        for(int j =0; j < N; j++){
            printf("%d ", input[i][j]);
        }
        printf("\n");
    }

}




int main(){
    /*
    struct rec r;
    struct rec r2; 
    struct rec r3;  
    //int arr[4] = {1,2,3,4}; 
    r.i = 10;
    r2.i = 11;
    r3.i = 12; 
    r.next = &r2; 
    r2.next = &r3; 
    r3.next = NULL;

    loop(&r);

    Example ex[3];
    printf("\nsizeof(recarray) %zu", sizeof(ex));


    struct klaa{
        int a;
        int b;
    }*klu;
    
    klu->a = 2;
    printf("%d", klu->a);

    test();
    test();
    test();*/
    /*
    int test[2][2] = {{1,1},{4,6},{7,9}};
    loop_2d_array(test);
    */
   
    //10^2 = 100 
    //with bit shifting


    FILE* fp = fopen("./output.txt", "a");
    fprintf(fp, "hello world\n");
    fclose(fp);

    return 0;
}