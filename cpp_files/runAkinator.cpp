#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ncurses.h>

#include "../h_files/nodeStruct.h"
#include "../h_files/newNodes.h"
#include "../h_files/runAkinator.h"

void createNode(node_t** ptrNode, newNode_t* newNodes);
void updateJSON(node_t* tree, const char* fileName);
void rewriteTreeJSON(node_t* tree, FILE* file, int indent);

void run(node_t** tree, const char* fileName, newNode_t* newNodes){
    printf("%s?\n", (*tree)->data);
    int c = 0;
    while ((c = getchar()) != 'y' && c != 'n') ;
    while (getchar() != '\n');
    if (c == 'y' && (*tree)->left != NULL)
    {
        if ((*tree)->left->left == NULL && (*tree)->left->right == NULL)
        {
            printf("I read your mind. It's %s\n", (*tree)->left->data);
        } 
        else
        {
            run(&((*tree)->left), fileName, newNodes);
        } 
    } 
    else if (c == 'n' && (*tree)->right != NULL)
    {
        if ((*tree)->right->left == NULL && (*tree)->right->right == NULL)
        {
            printf("I am loser. What did you wish for? Create new node:\n");
            createNode(&((*tree)->right), newNodes);
        }
        else 
        {
            run(&((*tree)->right), fileName, newNodes);
        }
    } else {
        printf("I am loser. What did you wish for? Create new node:\n");
        createNode(&((*tree)->right), newNodes);
    }
    updateJSON(*tree, fileName);
}

void createNode(node_t** ptrNode, newNode_t* newNodes){
    printf("New question: ");
    scanf("%s", newNodes->buffer);
    while (getchar() != '\n');
    printf("%s\n", newNodes->buffer);
    *ptrNode = (node_t*)calloc(1, sizeof(node_t));
    (*ptrNode)->data = newNodes->buffer;

    newNodes->freeSpace  += strlen(newNodes->buffer) + 1;
    printf("ptr node before: %s\n", (*ptrNode)->data);
    printf("Answer if \"yes\": ");
    scanf("%s", newNodes->buffer + newNodes->freeSpace);
    (*ptrNode)->left = (node_t*)calloc(1, sizeof(node_t));
    (*ptrNode)->left->data = newNodes->buffer;
    
    printf("ptr node after: %s\n", (*ptrNode)->data);

    newNodes->freeSpace += strlen(newNodes->buffer) + 1;
}

void updateJSON(node_t* tree, const char* fileName){
    FILE* file = fopen(fileName, "w");
    rewriteTreeJSON(tree, file, 0);
    fclose(file);
}

void rewriteTreeJSON(node_t* tree, FILE* file, int indent){
    int fullIndent = indent * 5 + (int)strlen(tree->data) + 1;
    
    fprintf(file, "%*s", indent * 5, "{\n");
    fprintf(file, "%*s\n", fullIndent, tree->data);

    if (tree->left != NULL)
        rewriteTreeJSON(tree->left, file, indent+1);
    if (tree->right != NULL)
        rewriteTreeJSON(tree->right, file, indent+1);

    fprintf(file, "%*s", indent * 5, "}\n");
}