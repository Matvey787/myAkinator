#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "readFile.h"
#include "tree.h"
#include "runAkinator.h"
#include "newNodes.h"
#include "graphDump.h"

int main(){
    system("rm -rf png_files");
    system("mkdir -p png_files");

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
    

    splitStrs += 2;
    node_t head = {splitStrs, NULL, NULL};
    splitStrs += (strlen(splitStrs) + 1);

    node_t* mainNode = &head;
    
    if (createTree(&splitStrs, &mainNode) != NO_ERRORS)
        return 1;
    

    writeDotFile(mainNode, "tree.dot");
    writePngFile("tree.dot", "png_files/");

    size_t radius = (numOfStrs - 1) / 6; // radius of a tree
    def_t* defPrefixes = (def_t*)calloc(radius, sizeof(def_t));

    if (defPrefixes == nullptr)
    {
        printf("allocate memory fail");
        return 1;
    }

    newNode_t newNodes = {0};
    printLeafDef(mainNode, "Alex R.", defPrefixes, 0);
    printLeafDef(mainNode, "subaru", defPrefixes, 0);

    run(&mainNode, "tree.json", &newNodes);

    delTree(mainNode);
    free(ptr_start_of_splitStrs);
    free(defPrefixes);
    free(buffer);
    return 0;
}
