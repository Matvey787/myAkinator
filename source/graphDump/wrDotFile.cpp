#include "graphDump.h"
#include <assert.h>

static void writeTreeToDotFile(node_t* node, FILE** wFile, size_t rank);

void writeDotFile(node_t* node, const char* fileName){
    assert(node != nullptr);
    assert(fileName != nullptr);
    
    FILE* wFile = fopen(fileName, "w");
    if (wFile == nullptr){
        printf("couldn't open file");
        return;
    }

    fprintf(wFile, "digraph\n{ \nrankdir=HR;\n");
    fprintf(wFile, "\n");

    writeTreeToDotFile(node, &wFile, 1);

    fprintf(wFile, "}\n");

    fclose(wFile);
}

static void writeTreeToDotFile(node_t* node, FILE** wFile, size_t rank){
    assert(node != nullptr);
    assert(wFile != nullptr);

    fprintf(*wFile, "node%p [ shape=record, rank = %lu, label= \"{ %p | %s | {<n%p_l> left | <n%p_r> right}} \" ];\n", 
                        node, rank, node, node->data, node, node);
    if (node->left != NULL)
    {
        writeTreeToDotFile(node->left, wFile, ++rank);
        fprintf(*wFile, "node%p:<n%p_l>:s -> node%p:n [ color = blue; ]\n", node, node, node->left);
    }
    if (node->right != NULL)
    {
        writeTreeToDotFile(node->right, wFile, ++rank);
        fprintf(*wFile, "node%p:<n%p_r>:s -> node%p:n [ color = red; ]\n", node, node, node->right);
    }
}