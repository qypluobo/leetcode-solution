#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "uthash.h"

struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};

#if 0
struct MyIntHashNode {
    int key;
    struct TreeNode* treeNode;
    UT_hash_handle hh;
};

typedef struct {
    struct TreeNode* root;
    int curIndex;
    int count;
    struct MyIntHashNode* hashTable;
} BSTIterator;

void bSTInorderWalk(struct TreeNode* root, BSTIterator* iterator)
{
    if (root == NULL) {
        return;
    }

    bSTInorderWalk(root->left, iterator);

    struct MyIntHashNode* node = (struct MyIntHashNode*)malloc(sizeof(struct MyIntHashNode));
    node->key = iterator->count;
    node->treeNode = root;
    HASH_ADD_INT(iterator->hashTable, key, node);
    iterator->count++;
    printf("%d ", root->val);

    bSTInorderWalk(root->right, iterator);
}

BSTIterator* bSTIteratorCreate(struct TreeNode* root) {
    BSTIterator* iterator = (BSTIterator*)malloc(sizeof(BSTIterator));
    iterator->root = root;
    iterator->curIndex = 0;
    iterator->count = 0;
    iterator->hashTable = NULL;

    bSTInorderWalk(root, iterator);
    printf("\n");
    return iterator;
}

/** @return the next smallest number */
int bSTIteratorNext(BSTIterator* obj) {
    if (obj->curIndex >= obj->count) {
        return 0;
    }

    struct MyIntHashNode* node = NULL;
    HASH_FIND_INT(obj->hashTable, &obj->curIndex, node);
    obj->curIndex++;
    return node->treeNode->val;
}

/** @return whether we have a next smallest number */
bool bSTIteratorHasNext(BSTIterator* obj) {
    if (obj->curIndex >= obj->count) {
        return false;
    }

    return true;
}

void bSTIteratorFree(BSTIterator* obj) {
    struct MyIntHashNode* node = NULL;
    struct MyIntHashNode* tmp = NULL;
    HASH_ITER(hh, obj->hashTable, node, tmp) {
        HASH_DEL(obj->hashTable, node);
        free(node);
    }
    free(obj);
}
#else
typedef struct {
    struct TreeNode** nodes;
    int count;
    int capacity;
} MyStack;

MyStack* stackCreate()
{
    MyStack* stack = (MyStack*)malloc(sizeof(MyStack));
    stack->nodes = NULL;
    stack->count = 0;
    stack->capacity = 0;
    return stack;
}

void stackPush(MyStack* stack, struct TreeNode* node)
{
    if (stack->capacity == stack->count) {
        struct TreeNode** tmp = (struct TreeNode**)realloc(stack->nodes, sizeof(struct TreeNode*) * (stack->count + 1));
        if (tmp == NULL) {
            return;
        }

        stack->capacity++;
        stack->nodes = tmp;
    }

    stack->nodes[stack->count++] = node;
}

struct TreeNode* stackPop(MyStack* stack)
{
    if (stack == NULL) {
        return NULL;
    }

    if (stack->count <= 0) {
        return NULL;
    }

    stack->count--;
    return stack->nodes[stack->count];
}

bool isStackEmpty(MyStack* stack)
{
    return stack->count == 0;
}

void stackDestroy(MyStack* stack)
{
    if (stack == NULL) {
        return;
    }

    printf("stack->capacity: %d\n", stack->capacity);

    if (stack->nodes != NULL) {
        free(stack->nodes);
    }
    stack->count = 0;
    stack->capacity = 0;
    free(stack);
}

typedef struct {
    MyStack* stack;
} BSTIterator;


BSTIterator* bSTIteratorCreate(struct TreeNode* root) {
    if (root == NULL) {
        return NULL;
    }

    BSTIterator* iterator = (BSTIterator*)malloc(sizeof(BSTIterator));
    iterator->stack = stackCreate();

    while (root != NULL) {
        stackPush(iterator->stack, root);
        root = root->left;
    }

    return iterator;
}

/** @return the next smallest number */
int bSTIteratorNext(BSTIterator* obj) {
    if (obj == NULL) {
        return 0;
    }

    struct TreeNode* node = stackPop(obj->stack);
    struct TreeNode* tmp = node->right;
    while (tmp != NULL) {
        stackPush(obj->stack, tmp);
        tmp = tmp->left;
    }

    return node->val;
}

/** @return whether we have a next smallest number */
bool bSTIteratorHasNext(BSTIterator* obj) {
    if (obj == NULL) {
        return false;
    }

    return isStackEmpty(obj->stack) == false;
}

void bSTIteratorFree(BSTIterator* obj) {
    if (obj == NULL) {
        return;
    }

    stackDestroy(obj->stack);
    free(obj);
}
#endif

void test1()
{
    struct TreeNode node1;
    struct TreeNode node2;
    struct TreeNode node3;
    struct TreeNode node4;
    struct TreeNode node5;

    node1.val = 5;
    node2.val = 1;
    node3.val = 7;
    node4.val = 6;
    node5.val = 9;

    node1.left = &node2;
    node1.right = &node3;

    node2.left = NULL;
    node2.right = NULL;

    node3.left = &node4;
    node3.right = &node5;

    node4.left = NULL;
    node4.right = NULL;

    node5.left = NULL;
    node5.right = NULL;

    BSTIterator* iterator = bSTIteratorCreate(&node1);

    while (bSTIteratorHasNext(iterator)) {
        printf("next: %d\n", bSTIteratorNext(iterator));
    }

    bSTIteratorFree(iterator);
}

int main()
{
    test1();
    return 0;
}