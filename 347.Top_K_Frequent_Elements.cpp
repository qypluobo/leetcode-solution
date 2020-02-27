#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "uthash.h"

typedef struct {
    int key;
    int count;
    UT_hash_handle hh;
} HashNode;

// smallest binary heap

void swap(int* a, int* b)
{
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

bool biggerThan(int a, int b) {
    return a > b;
}

void heapShiftUp(int* heap, int n, int k)
{
    int i;
    while (k > 0) {
        i = (k - 1) / 2;
        if (biggerThan(heap[i], heap[k])) {
            swap(&heap[i], &heap[k]);
            k = i;
        } else {
            break;
        }
    }
}

void heapShiftDown(int* heap, int n, int k)
{
    int i;
    while (2 * k + 1 < n) {
        i = 2 * k + 1;
        if (2 * k + 2 < n && biggerThan(heap[i], heap[2 * k + 2])) {
            i = 2 * k + 2;
        }

        if (biggerThan(heap[k], heap[i])) {
            swap(&heap[i], &heap[k]);
            k = i;
        } else {
            break;
        }
    }
}

void heapInsert(int* heap, int* n, int val)
{
    heap[*n] = val;
    *n += 1;
    heapShiftUp(heap, *n, *n - 1);
}

void heapDelete(int* heap, int* n)
{
    swap(&heap[0], &heap[*n - 1]);
    *n -= 1;
    heapShiftDown(heap, *n, 0);
}

void printArray(int* data, int n)
{
    for(int i = 0; i < n; i++) {
        printf("%d ", data[i]);
    }
    printf("\n");
}

int* topKFrequent(int* nums, int numsSize, int k, int* returnSize){
    int heapSize = 0;
    int i;
    HashNode* hashMap = NULL;
    HashNode* node = NULL;
    HashNode* tmp = NULL;
    HashNode* node2 = NULL;
    int* ans;

    // 统计数目
    for (i = 0; i < numsSize; i++) {
        HASH_FIND_INT(hashMap, &nums[i], node);
        if (node == NULL) {
            node = (HashNode*)malloc(sizeof(HashNode));
            node->key = nums[i];
            node->count = 1;
            HASH_ADD_INT(hashMap, key, node);
        } else {
            node->count++;
        }
    }

    // 最小堆，容量k
    HASH_ITER(hh, hashMap, node2, tmp) {
        HASH_FIND_INT(hashMap, &nums[0], node);

        if (heapSize == 0) {
            heapInsert(nums, &heapSize, node2->key);
        } else {
            if (node->count < node2->count || heapSize < k) {
                if (heapSize == k) {
                    heapDelete(nums, &heapSize);
                }
                heapInsert(nums, &heapSize, node2->key);
            }
        }
    }

    HASH_ITER(hh, hashMap, node, tmp) {
        printf("%d: %d\n", node->key, node->count);
        HASH_DEL(hashMap, node);
        free(node);
    }

    printf("heapSize: %d\n", heapSize);

    ans = (int*)malloc(sizeof(int) * k);
    for (i = 0; i < k; i++) {
        ans[i] = nums[i];
    }
    *returnSize = k;
    return ans;
}

void test1()
{
    int data[] = {1,1,1,2,2,3};
    int returnSize = 0;
    int* ans = topKFrequent(data, 6, 2, &returnSize);
    printArray(ans, 2);
}

void test2()
{
    int data[] = {1};
    int returnSize = 0;
    int* ans = topKFrequent(data, 1, 1, &returnSize);
    printArray(ans, 1);
}

void test3()
{
    int data[] = {4,1,-1,2,-1,2,3};
    int returnSize = 0;
    int* ans = topKFrequent(data, 7, 2, &returnSize);
    printArray(ans, 2);
}

int main()
{
    // test1();
    // test2();
    test3();
    return 0;
}