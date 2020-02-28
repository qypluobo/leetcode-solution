#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "uthash.h"

typedef struct {
    int v1;
    int v2;
} Pair;

// biggest binary heap

void swap(Pair** a, Pair** b)
{
    Pair* tmp = *a;
    *a = *b;
    *b = tmp;
}

bool lessThan(Pair* a, Pair* b) {
    return (a->v1 + a->v2) < (b->v1 + b->v2);
}

void heapShiftUp(Pair** heap, int n, int k)
{
    int i;
    while (k > 0) {
        i = (k - 1) / 2;
        if (lessThan(heap[i], heap[k])) {
            swap(&heap[i], &heap[k]);
            k = i;
        } else {
            break;
        }
    }
}

void heapShiftDown(Pair** heap, int n, int k)
{
    int i;
    while (2 * k + 1 < n) {
        i = 2 * k + 1;
        if (2 * k + 2 < n && lessThan(heap[i], heap[2 * k + 2])) {
            i = 2 * k + 2;
        }

        if (lessThan(heap[k], heap[i])) {
            swap(&heap[i], &heap[k]);
            k = i;
        } else {
            break;
        }
    }
}

void heapInsert(Pair** heap, int* n, Pair* val)
{
    heap[*n] = val;
    *n += 1;
    heapShiftUp(heap, *n, *n - 1);
}

void heapDelete(Pair** heap, int* n)
{
    swap(&heap[0], &heap[*n - 1]);
    *n -= 1;
    heapShiftDown(heap, *n, 0);
}

void printPairsList(Pair** pairs, int n)
{
    for(int i = 0; i < n; i++) {
        printf("[%d,%d] ", pairs[i]->v1, pairs[i]->v2);
    }
    printf("\n");
}

int** kSmallestPairs(int* nums1, int nums1Size, int* nums2, int nums2Size, int k, int* returnSize, int** returnColumnSizes){
    int i, j;
    int heapSize = 0;
    Pair** pairHeap = (Pair**)malloc(sizeof(Pair*) * k);
    int** ans;

    for (i = 0; i < nums1Size; i++) {
        for (j = 0; j < nums2Size; j++) {
            Pair* pair = (Pair*)malloc(sizeof(Pair));
            pair->v1 = nums1[i];
            pair->v2 = nums2[j];

            if (heapSize == 0 || lessThan(pair, pairHeap[0]) || heapSize < k) {
                if (heapSize == k) {
                    heapDelete(pairHeap, &heapSize);
                }

                heapInsert(pairHeap, &heapSize, pair);
            } else {
                free(pair);
            }
        }
    }

    printPairsList(pairHeap, heapSize);

    ans = (int**)malloc(sizeof(int*) * heapSize);
    *returnColumnSizes = (int*)malloc(sizeof(int) * heapSize);
    *returnSize = heapSize;
    for (i = 0; i < heapSize; i++) {
        ans[i] = (int*)malloc(sizeof(int) * 2);
        ans[i][0] = pairHeap[i]->v1;
        ans[i][1] = pairHeap[i]->v2;

        (*returnColumnSizes)[i] = 2;

        free(pairHeap[i]);
    }
    free(pairHeap);
    return ans;
}

void test1()
{
    int nums1[] = {1,7,11};
    int nums2[] = {2,4,6};

    int returnSize = 0;
    int* returnColumnSize = NULL;
    int** ans = kSmallestPairs(nums1, 3, nums2, 3, 3, &returnSize, &returnColumnSize);
}

void test2()
{
    int nums1[] = {1,1,2};
    int nums2[] = {1,2,3};

    int returnSize = 0;
    int* returnColumnSize = NULL;
    int** ans = kSmallestPairs(nums1, 3, nums2, 3, 2, &returnSize, &returnColumnSize);
}

void test3()
{
    int nums1[] = {1,2};
    int nums2[] = {3};

    int returnSize = 0;
    int* returnColumnSize = NULL;
    int** ans = kSmallestPairs(nums1, 2, nums2, 1, 3, &returnSize, &returnColumnSize);
}

int main()
{
    test1();
    test2();
    test3();
    return 0;
}