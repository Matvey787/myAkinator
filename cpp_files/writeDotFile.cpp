#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "../h_files/nodeStruct.h"
#include "../h_files/writeDotFile.h"

static void writeTree(node_t* node, FILE** wFile, size_t rank);

void writeDotFile(node_t* node, const char* fileName){
    FILE* wFile = fopen(fileName, "w");

    fprintf(wFile, "digraph\n{ \nrankdir=HR;\n");
    fprintf(wFile, "\n");

    writeTree(node, &wFile, 1);

    fprintf(wFile, "}\n");

    fclose(wFile);
}

static void writeTree(node_t* node, FILE** wFile, size_t rank){
    fprintf(*wFile, "node%p [ shape=record, rank = %lu, label= \"{ %p | %s | {<n%p_l> left | <n%p_r> right}} \" ];\n", 
                                                                                                node, rank, node, node->data, node, node);
    if (node->left != NULL)
    {
        writeTree(node->left, wFile, ++rank);
        fprintf(*wFile, "node%p:<n%p_l>:s -> node%p:n [ color = blue; ]\n", node, node, node->left);
    }
    if (node->right != NULL)
    {
        writeTree(node->right, wFile, ++rank);
        fprintf(*wFile, "node%p:<n%p_r>:s -> node%p:n [ color = red; ]\n", node, node, node->right);
    }
}