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

int lastStoneWeight(int* stones, int stonesSize){
    if (stones == NULL || stonesSize == 0) {
        return 0;
    }

    int* stonesHeap = (int*)malloc(sizeof(int) * stonesSize);
    int i, j, k, ans;

    memset(stonesHeap, 0, sizeof(int) * stonesSize);

    printArray(stones, stonesSize);

    // create heap
    stonesHeap[0] = stones[0];
    for (i = 1; i < stonesSize; i++) {
        stonesHeap[i] = stones[i];
        j = i;
        k = (j - 1) / 2;
        while (k >= 0) {
            if (stonesHeap[k] < stonesHeap[j]) {
                swap(&stonesHeap[k], &stonesHeap[j]);
                j = k;
                k = (j - 1) / 2;
            } else {
                break;
            }
        }
    }

    printArray(stonesHeap, stonesSize);

    // delete
    return 0;
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