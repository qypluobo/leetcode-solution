#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "uthash.h"

struct MyIntHashNode {
    int key;
    int val;
    UT_hash_handle hh;
};

struct MyStrHashNode {
    char* key;
    int val;
    UT_hash_handle hh;
};

void test1()
{
    struct MyStrHashNode* head = NULL;
    char testStr[] = "key0";

    printf("Add\n");
    for (int i = 0; i < 10; i++) {
        struct MyStrHashNode* node = (struct MyStrHashNode*)malloc(sizeof(struct MyStrHashNode));
        testStr[3] = i + '0';
        node->key = strdup(testStr);
        node->val = i;
        HASH_ADD_STR(head, key, node);
        printf("k-v: %s %d\n", node->key, node->val);
    }

    printf("Del\n");
    struct MyStrHashNode* tmp = NULL;
    struct MyStrHashNode* node = NULL;
    HASH_ITER(hh, head, node, tmp) {
        HASH_DEL(head, node);
        printf("k-v: %s %d\n", node->key, node->val);

        free(node->key);
    }
}

int main()
{
    test1();
    return 0;
}