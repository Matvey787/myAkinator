#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>

#include "tree.h"

void delTree(node_t* node){
    assert(node != nullptr);
    
    if (node->left != NULL)
        delTree(node->left);
    
    if (node->right != NULL)
        delTree(node->right);

    if (node->left != NULL)
        free(node->left);
    
    if (node->right != NULL)
        free(node->right);
}