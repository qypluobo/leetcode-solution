#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "uthash.h"

struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};

int count = 0;
bool find = false;
int ans = 0;

void inorderWalk(struct TreeNode* root, int k)
{
    if (root == NULL) {
        return;
    }

    inorderWalk(root->left, k);
    count++;
    if (count == k) {
        find = true;
        ans = root->val;
        return;
    }
    inorderWalk(root->right, k);
}

int kthSmallest(struct TreeNode* root, int k){
    count = 0;
    find = false;
    ans = 0;

    inorderWalk(root, k);
    return ans;
}

void test1()
{
}

int main()
{
    test1();
    return 0;
}