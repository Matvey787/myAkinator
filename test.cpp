#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int main(){
    char* buff = (char*)calloc(10, sizeof(char));
    buff[0] = '{';
    buff[1] = '\0';
    printf("%d", strcmp(buff, "{"));
}