#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "uthash.h"

void printArray(int* array, int size)
{
    for (int i = 0; i < size; i++) {
        printf("%d ", array[i]);
    }
    printf("\n");
}

void swap(int* a, int* b)
{
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

void heapInsert(int* stones, int k)
{
    int i;
    while (k > 0) {         // 直到当前节点为根节点时退出
        i = (k - 1) / 2;
        if (stones[i] < stones[k]) {
            swap(&stones[i], &stones[k]);
            k = i;
        } else {
            break;
        }
    }
}

int lastStoneWeight(int* stones, int stonesSize){
    if (stones == NULL || stonesSize == 0) {
        return 0;
    }

    int* stonesHeap = (int*)malloc(sizeof(int) * stonesSize);
    int i, ans;

    memset(stonesHeap, 0, sizeof(int) * stonesSize);

    printArray(stones, stonesSize);

    // create heap
    stonesHeap[0] = stones[0];
    for (i = 1; i < stonesSize; i++) {
        stonesHeap[i] = stones[i];
        heapInsert(stonesHeap, i);
    }

    printArray(stonesHeap, stonesSize);

    // delete
    return ans;
}

void test1()
{
    int stones[] = {2,7,4,1,8,1};
    int ans = lastStoneWeight(stones, sizeof(stones)/sizeof(stones[0]));
}

int main()
{
    test1();
    return 0;
}