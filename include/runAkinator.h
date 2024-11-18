#ifndef RUNAKINATOR
#define RUNAKINATOR

#include "tree.h"
#include "newNodes.h"
#include "errors.h"

error run(node_t** tree, const char* fileName, newNode_t* newNodes);

#endif