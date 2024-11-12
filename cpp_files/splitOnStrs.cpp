#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>

#include "../h_files/splitOnStrs.h"

void splitOnStrs(char* buffer, size_t numOfStrs, char* splitStrs){

    assert(buffer != nullptr);
    size_t i_buff = 0;
    size_t i_spltStrs = 0;
    int needDelSpaces = 0;

    while (numOfStrs > 0)
    {
        //fprintf(stderr, "%lu %lu %c\n", i_buff, numOfStrs, buffer[i_buff]);
        if (needDelSpaces)
        {
            while (buffer[i_buff] == ' ') ++i_buff;
            needDelSpaces = 0;
        }   

        if (buffer[i_buff] == '\n')
        {
            splitStrs[i_spltStrs++] = '\0';
            --numOfStrs;
            i_buff++;
            needDelSpaces = 1;
            continue;
        }
        splitStrs[i_spltStrs++] = buffer[i_buff++];
    }
}