#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "uthash.h"

struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};

bool isSubTreeBalanced(struct TreeNode* root, int* depth){
    if (root == NULL) {
        *depth = 0;
        return true;
    }

    int leftDepth = 0;
    int rightDepth = 0;

    bool leftBalanced = isSubTreeBalanced(root->left, &leftDepth);
    bool rightBalanced = isSubTreeBalanced(root->right, &rightDepth);

    *depth = leftDepth > rightDepth ? leftDepth : rightDepth;
    *depth += 1;

    printf("%d: %d %d, %d [%d, %d]\n", root->val, leftBalanced, rightBalanced, *depth, leftDepth, rightDepth);

    return leftBalanced && rightBalanced && (abs(leftDepth - rightDepth) <= 1);
}

bool isBalanced(struct TreeNode* root){
    int depth = 0;
    return isSubTreeBalanced(root, &depth);
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

    bool ans = isBalanced(&node1);
    printf("Balanced: %d\n", ans);
}

void test2()
{
    struct TreeNode node1;
    struct TreeNode node2;
    struct TreeNode node3;
    struct TreeNode node4;
    struct TreeNode node5;
    struct TreeNode node6;
    struct TreeNode node7;

    node1.val = 1;
    node2.val = 2;
    node3.val = 2;
    node4.val = 3;
    node5.val = 3;
    node6.val = 4;
    node7.val = 4;

    node1.left = &node2;
    node1.right = &node3;

    node2.left = &node4;
    node2.right = &node5;

    node3.left = NULL;
    node3.right = NULL;

    node4.left = &node6;
    node4.right = &node7;

    node5.left = NULL;
    node5.right = NULL;

    node6.left = NULL;
    node6.right = NULL;

    node7.left = NULL;
    node7.right = NULL;

    bool ans = isBalanced(&node1);
    printf("Balanced: %d\n", ans);
}

int main()
{
    test1();
    test2();
    return 0;
}