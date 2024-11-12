#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "../h_files/delTree.h"
#include "../h_files/nodeStruct.h"

void delTree(node_t* node){
    if (node->left != NULL)
        delTree(node->left);
    
    if (node->right != NULL)
        delTree(node->right);

    if (node->left != NULL)
        free(node->left);
    
    if (node->right != NULL)
        free(node->right);
}