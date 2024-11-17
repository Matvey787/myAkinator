#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>

#include "readFile.h"
#include "errors.h"

error splitOnStrs(char* buffer, size_t numOfStrs, char* splitStrs){
    assert(buffer != nullptr);
    assert(splitStrs != nullptr);

    if (buffer == nullptr || splitStrs == nullptr)
        return SPLIT_ON_STRS_FAIL;

    size_t i_buff = 0;
    size_t i_spltStrs = 0;
    int needDelSpaces = 0;

    while (numOfStrs > 0)
    {
        if (buffer[i_buff] == '\n')
        {
            splitStrs[i_spltStrs++] = '\0';
            --numOfStrs;
            i_buff++;
            needDelSpaces = 1;
            continue;
        }

        if (needDelSpaces)
        {
            while (isspace(buffer[i_buff])) ++i_buff;
            needDelSpaces = 0;
        }   
        splitStrs[i_spltStrs++] = buffer[i_buff++];
    }
    return NO_ERRORS;
}