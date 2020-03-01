#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "uthash.h"

void dfs(int** A, int ASize, int* AColSize, int i, int j)
{
    if (A[i][j] != 1) {
        return;
    }

    A[i][j] = 2;

    if (i - 1 >= 0) {
        dfs(A, ASize, AColSize, i - 1, j);
    }
    if (i + 1 < ASize) {
        dfs(A, ASize, AColSize, i + 1, j);
    }
    if (j + 1 < AColSize[i]) {
        dfs(A, ASize, AColSize, i, j + 1);
    }
    if (j - 1 >= 0) {
        dfs(A, ASize, AColSize, i, j - 1);
    }
}

int numEnclaves(int** A, int ASize, int* AColSize){
    int row, col;
    int ans = 0;

    for (row = 0; row < ASize; row++) {
        dfs(A, ASize, AColSize, row, 0);
        dfs(A, ASize, AColSize, row, AColSize[row] - 1);
    }

    for (col = 0; col < AColSize[0]; col++) {
        dfs(A, ASize, AColSize, 0, col);
    }

    for (col = 0; col < AColSize[ASize - 1]; col++) {
        dfs(A, ASize, AColSize, ASize - 1, col);
    }    

    for (row = 0; row < ASize; row++) {
        for (col = 0; col < AColSize[row]; col++) {
            if (A[row][col] == 1) {
                ans++;
            }
        }
    }

    return ans;
}

void test1()
{
    int data[][4] = {
        {0,0,0,0},
        {1,0,1,0},
        {0,1,1,0},
        {0,0,0,0}
    };
    int** A = (int**)malloc(sizeof(int*) * 4);
    int ASize = 4;
    int AColSize[4];

    int i;
    for (i = 0; i < 4; i++) {
        AColSize[i] = 4;
        A[i] = (int*)malloc(sizeof(int) * 4);
        memcpy(A[i], data[i], sizeof(int) * 4);
    }

    int ans = numEnclaves(A, ASize, AColSize);
    printf("%d\n", ans);
}

void test2()
{
    int data[][4] = {
        {0,1,1,0},
        {0,0,1,0},
        {0,0,1,0},
        {0,0,0,0}
    };
    int** A = (int**)malloc(sizeof(int*) * 4);
    int ASize = 4;
    int AColSize[4];

    int i;
    for (i = 0; i < 4; i++) {
        AColSize[i] = 4;
        A[i] = (int*)malloc(sizeof(int) * 4);
        memcpy(A[i], data[i], sizeof(int) * 4);
    }

    int ans = numEnclaves(A, ASize, AColSize);
    printf("%d\n", ans);
}

int main()
{
    test1();
    test2();
    return 0;
}