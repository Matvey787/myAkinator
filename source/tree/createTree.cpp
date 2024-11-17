#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>

#include "tree.h"
#include "errors.h"

error createTree(char** strs, node_t** node){
    assert(strs != nullptr);
    assert(node != nullptr);

    error status = NO_ERRORS;

    if (isalpha(*strs[0]))
    {
        (*node)->data = *strs;
        *strs += (strlen(*strs) + 1);
    }

    while (strcmp(*strs, "{") == 0){
        if (((*node) -> left) == NULL)
        {
            (*node)->left = (node_t*)calloc(1, sizeof(node_t));

            if ((*node)->left == nullptr)
            {
                printf("allocate memory fail");
                return ALLOCATE_MEMORY_FAIL;
            }

            ((*node)->left)->data = nullptr;
            ((*node)->left)->left = NULL;
            ((*node)->left)->right = NULL;

            *strs += 2; 
            status = createTree(strs, &(*node)->left);

            if (status == NO_ERRORS)
                continue;
            else
                return status;
        } 

        if ((*node)->right == NULL)
        {
            (*node)->right = (node_t*)calloc(1, sizeof(node_t));

            if ((*node)->right == nullptr)
            {
                printf("allocate memory fail");
                return ALLOCATE_MEMORY_FAIL;
            }

            (*node)->right->data  = nullptr;
            (*node)->right->left  = NULL;
            (*node)->right->right = NULL;

            *strs += 2;
            status = createTree(strs, &(*node)->right);

            if (status == NO_ERRORS)
                continue;
            else
                return status;
        }
    }
    
    if (strcmp(*strs, "}") == 0)
    {
        *strs += 2;
        return status;
    }
    return status;
}
