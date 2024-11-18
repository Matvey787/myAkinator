#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>

#include "tree.h"

error delTree(node_t* node){
    assert(node != nullptr);

    error status = NO_ERRORS;

    if (node == nullptr)
        return NULLPTR_ERROR;

    if (node->left != NULL)
        status = delTree(node->left);
    
    if (node->right != NULL)
        status = delTree(node->right);

    if (status != NO_ERRORS)
        return status;

    if (node->left != NULL)
        free(node->left);
    
    if (node->right != NULL)
        free(node->right);

    return status;
}