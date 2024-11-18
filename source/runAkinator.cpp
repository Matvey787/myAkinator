#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ncurses.h>
#include <assert.h>

#include "tree.h"
#include "newNodes.h"
#include "runAkinator.h"
#include "constants.h"

void createNode(node_t** ptrNode, newNode_t* newNodes);
void updateJSON(node_t* tree, const char* fileName);
void rewriteTreeJSON(node_t* tree, FILE* file, int indent);

error run(node_t** tree, const char* fileName, newNode_t* newNodes){
    assert(tree != nullptr);
    assert(fileName != nullptr);
    assert(newNodes != nullptr);
    error status = NO_ERRORS;
    
    if ((tree == nullptr) || (fileName == nullptr) || (newNodes == nullptr))
        return NULLPTR_ERROR;

    char phrase[c_length_of_strs] = {0};

    printf("%s?\n", (*tree)->data);
    sprintf(phrase, "espeak \"%s\"", (*tree)->data);
    system(phrase);

    int c = 0;

    while ((c = getchar()) != 'y' && c != 'n') ;
    while (getchar() != '\n');    

    if (c == 'y' && (*tree)->left != NULL)
    {
        if ((*tree)->left->left == NULL && (*tree)->left->right == NULL)
        {
            printf("I read your mind. It %s\n", (*tree)->left->data);
            sprintf(phrase, "espeak \"I read your mind. It's %s\"", (*tree)->left->data);
            system(phrase);
        } 
        else
        {
            status = run(&((*tree)->left), fileName, newNodes);
        } 
    } 
    else if (c == 'n' && (*tree)->right != NULL)
    {
        if ((*tree)->right->left == NULL && (*tree)->right->right == NULL)
        {
            printf("I am loser. What did you wish for? Create new node:\n");
            system("espeak \"I am loser. What did you wish for? Create new node\"");
            createNode(&((*tree)->right), newNodes);
        }
        else 
        {
            status = run(&((*tree)->right), fileName, newNodes);
        }
    } else {
        printf("I am loser. What did you wish for? Create new node:\n");
        system("espeak \"I am loser. What did you wish for? Create new node\"");
        createNode(&((*tree)->right), newNodes);
    }

    if (status != NO_ERRORS)
        return status;

    updateJSON(*tree, fileName);

    return status;
}

void createNode(node_t** ptrNode, newNode_t* newNodes){
    assert(ptrNode != nullptr);
    assert(newNodes != nullptr);

    printf("New question: ");
    scanf("%s", newNodes->newStr);

    while (getchar() != '\n');

    printf("%s\n", newNodes->newStr);
    *ptrNode = (node_t*)calloc(1, sizeof(node_t));
    (*ptrNode)->data = newNodes->newStr;
    newNodes->freeSpace  += strlen(newNodes->newStr) + 1;

    printf("Answer if \"yes\": ");
    scanf("%s", newNodes->newStr + newNodes->freeSpace);
    
    (*ptrNode)->left = (node_t*)calloc(1, sizeof(node_t));
    (*ptrNode)->left->data = newNodes->newStr + newNodes->freeSpace;

    newNodes->freeSpace += strlen(newNodes->newStr + newNodes->freeSpace) + 1;
}

void updateJSON(node_t* tree, const char* fileName){
    assert(tree != nullptr);
    assert(fileName != nullptr);

    FILE* file = fopen(fileName, "w");
    rewriteTreeJSON(tree, file, 0);
    fclose(file);
}

void rewriteTreeJSON(node_t* tree, FILE* file, int indent){
    assert(tree != nullptr);
    assert(file != nullptr);

    int fullIndent = indent * c_tab + (int)strlen(tree->data);
    
    fprintf(file, "%*s", indent * c_tab + 2, "{\n");
    fprintf(file, "%*s\n", fullIndent, tree->data);

    if (tree->left != NULL)
        rewriteTreeJSON(tree->left, file, indent+1);
    if (tree->right != NULL)
        rewriteTreeJSON(tree->right, file, indent+1);

    fprintf(file, "%*s", indent * c_tab + 2, "}\n");
}