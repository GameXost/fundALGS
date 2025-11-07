#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>


typedef struct TreeNode{
    int data;
    struct TreeNode* pleft;
    struct TreeNode* pright;
} TreeNode;


void FindAndInsert(struct TreeNode **pRoot, int value) {
    struct TreeNode* ptr = *pRoot;
    if (*pRoot == NULL) {
        *pRoot = (struct TreeNode*)malloc(sizeof( TreeNode));
        if (*pRoot == NULL) {
            return;
        }
        (*pRoot) -> data = value;
        (*pRoot) -> pleft = (*pRoot)->pright;
    }
    if (ptr->data == value) {
        printf("exists");
        return;
    }
    if (value < ptr ->data) {
        FindAndInsert(&ptr->pleft, value);
    }
    if (value>ptr->data) {
        FindAndInsert(&ptr->pright, value);
    }
}


//iterative loop
void FindAndInsertLoop( TreeNode **pRoot, int value) {
    int side = 0;
    TreeNode* ptr = *pRoot;
    TreeNode* root = NULL;
    while (ptr != NULL) {
        if (ptr->data == value) {
            printf("ok");
            return;
        }
        if (ptr->data < value) {
            root = ptr;
            side = 1;
            ptr = ptr->pright;
            continue;
        }
        if (ptr->data > value) {
            root = ptr;
            side = 0;
            ptr = ptr->pleft;
        }
    }
    //init ptr here in case it's null
    if (side == 0) {
        root->pleft = ptr;
    }else {
        root->pright = ptr;
    }



}
