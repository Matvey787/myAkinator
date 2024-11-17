#ifndef TREE
#define TREE

#include "errors.h"

struct node_t
{
    char* data;
    node_t* left;
    node_t* right;
};

struct def_t
{
    char* str;
    short truth;
};

error createTree(char** strs, node_t** node);
void delTree(node_t* node);

void printLeafDef(const node_t* node, const char* leafName, def_t* defParts, size_t i_dP);

#endif