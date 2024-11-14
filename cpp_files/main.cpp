#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "../h_files/readFile.h"
#include "../h_files/nodeStruct.h"
#include "../h_files/splitOnStrs.h"
#include "../h_files/createTree.h"
#include "../h_files/delTree.h"
#include "../h_files/writeDotFile.h"
#include "../h_files/printLeafDef.h"
#include "../h_files/runAkinator.h"
#include "../h_files/newNodes.h"

int writePngFile(const char* dotFile, const char* directory);

int main(){
    system("rm -rf png_files");
    system("mkdir -p png_files");

    char* buffer = nullptr;
    size_t numOfSmbls = 0;
    size_t numOfStrs = 0;
    readFile(&buffer, "tree.json", &numOfSmbls, &numOfStrs);

    //printf("%lu\n", numOfStrs);
    
    char* splitStrs = (char*)calloc(numOfSmbls+1, sizeof(char));

    if (splitStrs == nullptr)
    {
        printf("allocate memory fail");
        return 1;
    }

    char* ptr_start_of_splitStrs = splitStrs;
    splitOnStrs(buffer, numOfStrs, splitStrs);
    
    /* int k =0;
    for (int i = 0; i < numOfStrs; i++){
        printf("----%s\n", splitStrs+k);
        k += strlen(splitStrs)+1;
    } */

    splitStrs += 2;
    node_t head = {splitStrs, NULL, NULL};
    splitStrs += (strlen(splitStrs) + 1);

    node_t* mainNode = &head;
    
    createTree(&splitStrs, &mainNode);
    writeDotFile(mainNode, "tree.dot");
    writePngFile("tree.dot", "png_files/");

    size_t radius = (numOfStrs - 1) / 6; // radius of a tree
    def_t* defParts = (def_t*)calloc(radius, sizeof(def_t));
    //printLeafDef(mainNode, "Poltorashka", defParts, 0);

    newNode_t newNodes = {0};
    run(&mainNode, "tree.json", &newNodes);

    delTree(mainNode);
    free(ptr_start_of_splitStrs);
    free(defParts);
    free(buffer);
    return 0;
}

int writePngFile(const char* dotFile, const char* directory){
    assert(dotFile != nullptr);
    static int numOfCall = 0;
    char command[100];
    sprintf(command, "dot %s -Tpng -o %spicture%d.png", dotFile, directory, numOfCall++);
    system(command);

    return numOfCall;
}
