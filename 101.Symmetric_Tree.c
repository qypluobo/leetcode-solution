#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "uthash.h"

struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};

int isSame(struct TreeNode* a, struct TreeNode* b)
{
    if (a == NULL && b == NULL) {
        return 1;
    } else if (a == NULL || b == NULL) {
        return 0;
    }

    int leftSame = isSame(a->left, b->right);
    int rightSame = isSame(a->right, b->left);

    return a->val == b->val && leftSame && rightSame ? 1 : 0;
}

int isSymmetric(struct TreeNode* root) {
    if (root == NULL) {
        return 1;
    }

    int same = isSame(root->left, root->right);

    return same;
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

    int isSym = isSymmetric(&node1);
    printf("isSym: %d\n", isSym);
}

void test2()
{
    struct TreeNode node1;
    struct TreeNode node2;
    struct TreeNode node3;
    struct TreeNode node4;
    struct TreeNode node5;

    node1.val = 1;
    node2.val = 2;
    node3.val = 2;
    node4.val = 3;
    node5.val = 3;

    node1.left = &node2;
    node1.right = &node3;

    node2.left = &node4;
    node2.right = NULL;

    node3.left = NULL;
    node3.right = &node5;

    node4.left = NULL;
    node4.right = NULL;

    node5.left = NULL;
    node5.right = NULL;

    int isSym = isSymmetric(&node1);
    printf("isSym: %d\n", isSym);
}

void test3()
{
    struct TreeNode node1;
    struct TreeNode node2;
    struct TreeNode node3;
    struct TreeNode node4;
    struct TreeNode node5;

    node1.val = 1;
    node2.val = 2;
    node3.val = 2;
    node4.val = 3;
    node5.val = 3;

    node1.left = &node2;
    node1.right = &node3;

    node2.left = &node4;
    node2.right = NULL;

    node3.left = &node5;
    node3.right = NULL;

    node4.left = NULL;
    node4.right = NULL;

    node5.left = NULL;
    node5.right = NULL;

    int isSym = isSymmetric(&node1);
    printf("isSym: %d\n", isSym);
}

int main()
{
    test1();
    test2();
    return 0;
}