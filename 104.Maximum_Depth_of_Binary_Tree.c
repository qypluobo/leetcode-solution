#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "uthash.h"

struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};

int g_deepth = 0;

void getMaxDepth(struct TreeNode* root, int deepth)
{
    if (root == NULL) {
        return;
    }

    if (root->left == NULL || root->right == NULL) {
        g_deepth = g_deepth >= deepth ? g_deepth : deepth;
    }

    getMaxDepth(root->left, deepth + 1);
    getMaxDepth(root->right, deepth + 1);
}

int maxDepthSolution1(struct TreeNode* root){
    g_deepth = 0;
    getMaxDepth(root, 1);
    return g_deepth;
}

int maxDepthSolution2(struct TreeNode* root){
    if (root == NULL) {
        return 0;
    }

    int leftDepth = maxDepthSolution2(root->left);
    int rightDepth = maxDepthSolution2(root->right);

    return leftDepth >= rightDepth ? leftDepth + 1 : rightDepth + 1;
}

void test1()
{
    struct TreeNode node1;
    struct TreeNode node2;
    struct TreeNode node3;
    struct TreeNode node4;
    struct TreeNode node5;

    node1.val = 3;
    node2.val = 9;
    node3.val = 20;
    node4.val = 15;
    node5.val = 7;

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

    int deepth = maxDepthSolution1(&node1);
    printf("deepth: %d\n", deepth);
}

void test2()
{
    struct TreeNode node1;
    struct TreeNode node2;
    struct TreeNode node3;
    struct TreeNode node4;
    struct TreeNode node5;

    node1.val = 3;
    node2.val = 9;
    node3.val = 20;
    node4.val = 15;
    node5.val = 7;

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

    int deepth = maxDepthSolution2(&node1);
    printf("deepth: %d\n", deepth);
}

int main()
{
    test1();
    test2();
    return 0;
}