#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "uthash.h"

struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};

bool findPathSum(struct TreeNode* root, int curSum, int targetSum)
{
    if (root->left == NULL && root->right == NULL) {
        if (curSum == targetSum) {
            return true;
        } else {
            return false;
        }
    }

    bool leftHas = false;
    bool rightHas = false;

    if (root->left) {
        leftHas = findPathSum(root->left, curSum + root->left->val, targetSum);
    }

    if (root->right) {
        rightHas = findPathSum(root->right, curSum + root->right->val, targetSum);
    }

    return leftHas || rightHas;
}

bool hasPathSum(struct TreeNode* root, int sum){
    if (root == NULL) {
        return false;
    }
    return findPathSum(root, root->val, sum);
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

    bool has = hasPathSum(&node1, 12);
    printf("has: %d\n", has);
}

int main()
{
    test1();
    return 0;
}