#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "uthash.h"

struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};

int sum = 0;

void inorderWalk(struct TreeNode* root)
{
    if (root == NULL) {
        return;
    }

    inorderWalk(root->right);
    sum += root->val;
    root->val = sum;
    inorderWalk(root->left);
}

struct TreeNode* bstToGst(struct TreeNode* root){
    sum = 0;

    inorderWalk(root);
    return root;
}

void test1()
{
    struct TreeNode node1;
    struct TreeNode node2;
    struct TreeNode node3;
    struct TreeNode node4;
    struct TreeNode node5;
    struct TreeNode node6;
    struct TreeNode node7;
    struct TreeNode node8;
    struct TreeNode node9;

    node1.val = 4;
    node2.val = 1;
    node3.val = 6;
    node4.val = 0;
    node5.val = 2;
    node6.val = 5;
    node7.val = 7;
    node8.val = 3;
    node9.val = 8;

    node1.left = &node2;
    node1.right = &node3;

    node2.left = &node4;
    node2.right = &node5;

    node3.left = &node6;
    node3.right = &node7;

    node4.left = NULL;
    node4.right = NULL;

    node5.left = NULL;
    node5.right = &node8;

    node6.left = NULL;
    node6.right = NULL;

    node7.left = NULL;
    node7.right = &node9;

    node8.left = NULL;
    node8.right = NULL;

    node9.left = NULL;
    node9.right = NULL;

    struct TreeNode* node = bstToGst(&node1);
}

int main()
{
    test1();
    return 0;
}