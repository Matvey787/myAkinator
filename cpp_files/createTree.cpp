#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>

#include "../h_files/nodeStruct.h"
#include "../h_files/createTree.h"

// buffer = {\0ON MIPT"\0{\0People"\0}\0}\0

void createTree(char** buffer, node_t** node){
    assert(buffer != nullptr);
    assert(node != nullptr);

    //printf("%s %d\n", *buffer, strcmp(*buffer, "{"));
    if (isalpha(*buffer[0]))
    {
        (*node)->data = *buffer;
        *buffer += (strlen(*buffer) + 1);
    }

    while (strcmp(*buffer, "{") == 0){
        if (((*node) -> left) == NULL)
        {
            (*node)->left = (node_t*)calloc(1, sizeof(node_t));

            if ((*node)->left == nullptr)
            {
                printf("allocate memory fail");
                return;
            }

            ((*node)->left)->data = nullptr;
            ((*node)->left)->left = NULL;
            ((*node)->left)->right = NULL;

            *buffer += 2;
            createTree(buffer, &((*node)->left));
            continue;
        } 

        if (((*node) -> right) == NULL)
        {
            (*node)->right = (node_t*)calloc(1, sizeof(node_t));

            if ((*node)->right == nullptr)
            {
                printf("allocate memory fail");
                return;
            }

            ((*node)->right)->data = nullptr;
            ((*node)->right)->left = NULL;
            ((*node)->right)->right = NULL;

            *buffer += 2;
            createTree(buffer, &((*node)->right));
            continue;
        }
    }
    

    if (strcmp(*buffer, "}") == 0)
    {
        *buffer += 2;
        return;
    }

}
