#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "tree.h"

void printLeafDef(const node_t* node, const char* leafName, def_t* defParts, size_t i_dP){
    assert(node != nullptr);
    assert(leafName != nullptr);
    assert(defParts != nullptr);
    
    if (node->left == NULL && node->right == NULL)
    {
        if (strcmp(leafName, node->data) == 0)
        {
            printf("%s", node->data);
            for (size_t i = 0; i < i_dP; i++)
            {
                
                defParts[i].truth ? printf(" %s", defParts[i].str) : printf("\033[31m not %s \033[37m", defParts[i].str);
            }
            printf("\n");
        }
    } 

    if (node->left != NULL)
    {
        defParts[i_dP].str = node->data;
        defParts[i_dP].truth = 1;
        printLeafDef(node->left, leafName, defParts, i_dP + 1);
    }

    if (node->right != NULL)
    {
        defParts[i_dP].str = node->data;
        defParts[i_dP].truth = 0;
        printLeafDef(node->right, leafName, defParts, i_dP + 1);
    }
    return;
}