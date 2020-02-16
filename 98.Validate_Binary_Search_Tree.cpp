#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include "uthash.h"

struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};

bool isValidSubBST(struct TreeNode* root, long minVal, long maxVal){
    if (root == NULL) {
        return true;
    }

    if (root->val <= minVal) {
        return false;
    }

    if (root->val >= maxVal) {
        return false;
    }

    return isValidSubBST(root->left, minVal, root->val) && isValidSubBST(root->right, root->val, maxVal);
}

bool isValidBST(struct TreeNode* root){
    return isValidSubBST(root, LONG_MIN, LONG_MAX);
}

void test1()
{
    struct TreeNode node1;
    struct TreeNode node2;
    struct TreeNode node3;

    node1.val = 2;
    node2.val = 1;
    node3.val = 3;

    node1.left = &node2;
    node1.right = &node3;

    node2.left = NULL;
    node2.right = NULL;

    node3.left = NULL;
    node3.right = NULL;

    bool valid = isValidBST(&node1);
    printf("valid: %d\n", valid);
}

void test2()
{
    struct TreeNode node1;
    struct TreeNode node2;
    struct TreeNode node3;
    struct TreeNode node4;
    struct TreeNode node5;

    node1.val = 5;
    node2.val = 1;
    node3.val = 4;
    node4.val = 3;
    node5.val = 6;

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

    bool valid = isValidBST(&node1);
    printf("valid: %d\n", valid);
}

void test3()
{
    struct TreeNode node1;
    struct TreeNode node2;
    struct TreeNode node3;
    struct TreeNode node4;
    struct TreeNode node5;

    node1.val = 5;
    node2.val = 1;
    node3.val = 7;
    node4.val = 3;
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

    bool valid = isValidBST(&node1);
    printf("valid: %d\n", valid);
}

int main()
{
    test1();
    test2();
    test3();
    return 0;
}