#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void)
{
    char a[] = {'h','e','l','l','o','\0'};
    char*b = calloc(6, sizeof(char));
    memcpy(b,a,strlen(a));
    printf("%s", b);
    printf("%s", a);
    return 0;
}