#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "uthash.h"

struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};

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
    printf("count: %d\n", iterator->count);

    while (bSTIteratorHasNext(iterator)) {
        printf("next: %d\n", bSTIteratorNext(iterator));
    }
}

int main()
{
    test1();
    return 0;
}