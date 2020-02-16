#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "uthash.h"

struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};

struct TreeNode* findSuccessor(struct TreeNode* root)
{
    root = root->right;
    while (root->left != NULL) {
        root = root->left;
    }
    return root;
}

struct TreeNode* deleteNode(struct TreeNode* root, int key){
    if (root == NULL) {
        return NULL;
    }

    if (root->val > key) {
        // 从左子树删除
        root->left = deleteNode(root->left, key);
        return root;
    } else if (root->val < key) {
        // 从右子树删除
        root->right = deleteNode(root->right, key);
        return root;
    }

    // 找到了值为key的节点
    if (root->left == NULL) {
        // 左子树为空，则直接使用右子树代替
        return root->right;
    } else if (root->right == NULL) {
        // 右子树为空，则直接使用左子树代替
        return root->left;
    } else {
        // 1，当前节点 和 后继节点交换
        // 2，删除交换后的后继节点（值依然为key）
        struct TreeNode* successor = findSuccessor(root);
        int tmp = successor->val;
        successor->val = root->val;
        root->val = tmp;

        root->right = deleteNode(root->right, key);   // 在交换后的树中 继续删除
    }

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

    node1.val = 5;
    node2.val = 3;
    node3.val = 6;
    node4.val = 2;
    node5.val = 4;
    node6.val = 7;

    node1.left = &node2;
    node1.right = &node3;

    node2.left = &node4;
    node2.right = &node5;

    node3.left = NULL;
    node3.right = &node6;

    node4.left = NULL;
    node4.right = NULL;

    node5.left = NULL;
    node5.right = NULL;

    node6.left = NULL;
    node6.right = NULL;

    struct TreeNode* node = deleteNode(&node1, 3);
}

int main()
{
    test1();
    return 0;
}