#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "uthash.h"

void printIntArray(int** data, int n, int m)
{
    int i, j;

    for (i = 0; i < n; i++) {
        for (j = 0; j < m; j++) {
            printf("%d ", data[i][j]);
        }
        printf("\n");
    }
}

void printCharArray(char** data, int n)
{
    int i;

    for (i = 0; i < n; i++) {
        printf("%s\n", data[i]);
    }
}

void test1()
{
    int SIZE = 100;
    int n = 0;
    int m = 0;
    int** data = (int**)malloc(sizeof(int*) * SIZE);
    int i, j;

    for (i = 0; i < SIZE; i++) {
        data[i] = (int*)malloc(sizeof(int) * SIZE);
    }
    
    scanf("%d %d", &n, &m);

    printf("[%d, %d]\n", n, m);

    for (i = 0; i < n; i++) {
        for (j = 0; j < m; j++) {
            scanf("%d", &data[i][j]);
        }
    }

    printIntArray(data, n, m);
}

void test2()
{
    int SIZE = 100;
    int n = 0;
    char** data = (char**)malloc(sizeof(char*) * SIZE);
    int i;

    for (i = 0; i < SIZE; i++) {
        data[i] = (char*)malloc(sizeof(char) * SIZE);
        memset(data[i], 0, sizeof(char) * SIZE);
    }
    
    scanf("%d", &n);

    printf("[%d]\n", n);

    for (i = 0; i < n; i++) {
        scanf(" %[^\n]", data[i]);
    }

    printCharArray(data, n);
}

int main()
{
    // test1();
    test2();
    return 0;
}