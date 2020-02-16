#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "uthash.h"

struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};

struct MyHashNode {
    int key;
    int val;
    UT_hash_handle hh;
};

struct MyHashNode* inHash = NULL;

struct TreeNode* buildSubTree(int* inorder, int iStart, int iEnd, int* postorder, int pStart, int pEnd){
    printf("[%d, %d], [%d, %d]\n", iStart, iEnd, pStart, pEnd);

    if (iStart > iEnd || iEnd < 0 || pStart > pEnd || pEnd < 0) {
        return NULL;
    }

    struct TreeNode* root = (struct TreeNode*)malloc(sizeof(struct TreeNode));

    if (iStart == iEnd) {
        root->val = inorder[iStart];
        root->left = NULL;
        root->right = NULL;
        return root;
    }

    int pRoot = pEnd;

    struct MyHashNode* tmp = NULL;
    HASH_FIND_INT(inHash, &postorder[pRoot], tmp);
    int iRoot = tmp->val;

    printf("iRoot: %d, pRoot: %d\n", iRoot, pRoot);
    
    root->val = postorder[pRoot];
    // 使用中序 确定 左右子树的长度
    // 使用后序 的起点 确定左子树的 终点 以及 右子树的起点，右子树的终点为根节点 向左偏移1
    root->left = buildSubTree(inorder, iStart, iRoot - 1, postorder, pStart, pStart + iRoot - iStart - 1);
    root->right = buildSubTree(inorder, iRoot + 1, iEnd, postorder, pStart + iRoot - iStart, pRoot - 1);

    return root;
}

struct TreeNode* buildTree(int* inorder, int inorderSize, int* postorder, int postorderSize){
    if (inorder == NULL || inorderSize == 0 || postorder == NULL || postorderSize == 0) {
        return NULL;
    }

    int i;
    struct MyHashNode* tmp  = NULL;
    for (i = 0; i < inorderSize; i++) {
        tmp = (struct MyHashNode*)malloc(sizeof(struct MyHashNode));
        tmp->key = inorder[i];
        tmp->val = i;
        HASH_ADD_INT(inHash, key, tmp);
    }

    struct TreeNode* root = buildSubTree(inorder, 0, inorderSize - 1, postorder, 0, postorderSize - 1);

    struct MyHashNode* curItem = NULL;
    HASH_ITER(hh, inHash, curItem, tmp) {
        HASH_DEL(inHash, curItem);
        free(curItem);
    }

    return root;
}

void test1()
{
    int inorder[] = {9, 3, 15, 20, 7};
    int postorder[] = {9, 15, 7, 20, 3};

    struct TreeNode* root = buildTree(inorder, 5, postorder, 5);
    printf("root: %d\n", root->val);
}

void test2()
{
    int inorder[] = {2, 1};
    int postorder[] = {2, 1};

    struct TreeNode* root = buildTree(inorder, 2, postorder, 2);
    printf("root: %d\n", root->val);
}

void test3()
{
    int inorder[] = {2, 3, 1};
    int postorder[] = {3, 2, 1};

    struct TreeNode* root = buildTree(inorder, 3, postorder, 3);
    printf("root: %d\n", root->val);
}

void test4()
{
    int inorder[] = {1, 2, 3, 4};
    int postorder[] = {3, 4, 2, 1};

    struct TreeNode* root = buildTree(inorder, 4, postorder, 4);
    printf("root: %d\n", root->val);
}

int main()
{
    test4();
    return 0;
}
