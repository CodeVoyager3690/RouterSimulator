#include <stdio.h>
#include <stdlib.h>
#include <ctype.h> 
#include <string.h>

typedef struct{
    char*key; 
    char*value; 
}Assoc;


void sort(Assoc input[], int size);
void printMap(Assoc map[], int size);
char* get_value(Assoc input[], int size, char*key,int min, int max, FILE *fp);

int main() {
    
    Assoc map[] = {
        {"bilal", "cool"},
        {"billy", "ya"},
        {"jon jones", "bad"},
        {"messi", "good"},
        {"gsp", "goat"}
    };
    printf("mapsize: %d\n", sizeof(map) / (2*sizeof(char*)));
    int elements = sizeof(map) / (2*sizeof(char*));
    printMap(map, elements);
    sort(map, elements);
    printMap(map, elements);

    FILE *fp = fopen("out.txt", "w"); 
    printf("%s", get_value(map, elements, "mesi", 0, elements, fp));
    fclose(fp);
    return 0; 
}

void printMap(Assoc map[], int size)
{
    for(int i = 0; i < size; i++){
        printf("{%s %s}\n", map[i].key, map[i].value);
    }
}

void sort(Assoc input[], int size){
    for(int i = 0; i < size-1; i++){
        for(int j = i+1; j < size-1; j++){
            char* left = input[j].key; 
            char* right = input[j+1].key; 
            if(strcmp(left,right) > 0){
                Assoc copy = input[j+1]; 
                input[j+1] = input[j]; 
                input[j] = copy;
            }
        }
    }
}
//binary search
char* get_value(Assoc input[], int size, char*key,int min, int max, FILE *fp){

    fprintf(fp,"min %d max %d mid %d\n", min, max, (min + max)/2);
    int mid = (min+max)/2;
    if(mid == min || mid == max){
        return "not found";
    }
    if(strcmp(key, input[mid].key) == 0){
        return input[mid].value;
    }
    if((strcmp(key, input[mid].key) < 0))
    {
        return get_value(input, size, key, min, mid, fp); 
    }
    if((strcmp(key, input[mid].key) > 0))
    {
        return get_value(input, size, key, mid, max, fp );
    }
    
}




