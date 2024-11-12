#include <stdio.h>
#include <stdlib.h>

#include "../h_files/readFile.h"

void readFile(char** buffer, const char* file_name, size_t* numOfSymbols, size_t* numOfStrs){

    // open file for read

    FILE* rFile = fopen(file_name, "rb");

    // find size of file

    fseek(rFile, 0, SEEK_END);
    *numOfSymbols = (size_t)ftell(rFile);
    fseek(rFile, 0, SEEK_SET);

    // read text from file

    *buffer = (char*)calloc(*numOfSymbols, sizeof(char));
    fread(*buffer, sizeof(char), *numOfSymbols, rFile);

    // find number of strings
    for (size_t i = 0; i < *numOfSymbols; i++) if ((*buffer)[i] == '\n') ++(*numOfStrs);

    // close file 

    fclose(rFile);

}