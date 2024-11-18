#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "readFile.h"
#include "tree.h"
#include "constants.h"
#include "runAkinator.h"
#include "newNodes.h"
#include "graphDump.h"

// rm -rf png_files

const char* c_default_directory_for_saving_pictures = "png_files/";

int main(int argc, char *argv[]){
    char directory[c_length_of_strs] = {0};
    //printf("%d %s", argc, argv[1]);
    if (argc > 1)
    {
        sprintf(directory, "%s/", argv[1]);
    }
    else 
    {
        sprintf(directory, "%s/", c_default_directory_for_saving_pictures);
        system("mkdir -p png_files");
    }
    printf("%s\n", directory);
    char* buffer = nullptr;
    size_t numOfSmbls = 0;
    size_t numOfStrs = 0;
    if (readFile(&buffer, "tree.json", &numOfSmbls, &numOfStrs) != NO_ERRORS){
        return 1;
    }
    
    char* splitStrs = (char*)calloc(numOfSmbls+1, sizeof(char));

    if (splitStrs == nullptr)
    {
        printf("allocate memory fail\n");
        return 1;
    }

    char* ptr_start_of_splitStrs = splitStrs;
    
    if (splitOnStrs(buffer, numOfStrs, splitStrs) != NO_ERRORS)
        return 1;
    

    splitStrs += 2; // it's {\n in json file (2 symbols)
    node_t head = {splitStrs, NULL, NULL};
    splitStrs += (strlen(splitStrs) + 1);

    node_t* mainNode = &head;
    
    if (createTree(&splitStrs, &mainNode) != NO_ERRORS)
        return 1;
    

    writeDotFile(mainNode, "tree.dot");
    writePngFile("tree.dot", directory);

    size_t numOfNodes = (numOfStrs - 1) / 6; // number of nodes of a tree
    def_t* defPrefixes = (def_t*)calloc(numOfNodes, sizeof(def_t));

    if (defPrefixes == nullptr)
    {
        printf("allocate memory fail");
        return 1;
    }

    newNode_t newNodes = {0};
    printLeafDef(mainNode, "Alex R.", defPrefixes, 0);
    printLeafDef(mainNode, "subaru", defPrefixes, 0);

    if (run(&mainNode, "tree.json", &newNodes) != NO_ERRORS)
        return 1;

    if (delTree(mainNode) != NO_ERRORS)
        return 1;

    free(ptr_start_of_splitStrs);
    free(defPrefixes);
    free(buffer);
    return 0;
}
