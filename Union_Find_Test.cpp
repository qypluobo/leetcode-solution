#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "uthash.h"

int* parent = NULL;
int* weight = NULL;

int findRootByRecursion(int x)
{
    if (x == parent[x]) {
        return x;
    }

    parent[x] = findRootByRecursion(parent[x]);
    return parent[x];
}

int findRootByIteration(int x)
{
    while (x != parent[x]) {
        parent[x] = parent[parent[x]];
        x = parent[x];
    }

    return x;
}

void join(int a, int b)
{
    int roota = findRootByIteration(a);
    int rootb = findRootByIteration(b);

    if (weight[roota] >= weight[rootb]) {
        parent[roota] = rootb;
        weight[rootb] += weight[roota];
    } else {
        parent[rootb] = roota;
        weight[roota] += weight[rootb];
    }
}

void printArray(int* array, int n)
{
    for (int i = 0; i < n; i++) {
        printf("%d ", array[i]);
    }
    printf("\n");
}

void test1()
{
    int n = 10;
    int i;

    parent = (int*)malloc(sizeof(int) * n);
    weight = (int*)malloc(sizeof(int) * n);
    for (i = 0; i < n; i++) {
        parent[i] = i;
        weight[i] = 1;
    }

    printArray(parent, n);
    printArray(weight, n);

    for (i = 1; i < n; i++) {
        join(0, i);
    }

    //findRootByRecursion(1);
    //findRootByRecursion(0);

    for (i = 0; i < n; i++) {
        findRootByIteration(i);
    }
    findRootByIteration(1);
    findRootByIteration(2);

    printArray(parent, n);
    printArray(weight, n);
}

int main()
{
    test1();
    return 0;
}