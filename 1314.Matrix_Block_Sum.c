#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "uthash.h"

int getMatVal(int** mat, int matSize, int* matColSize, int i, int j) {
    if (i < 0 || j < 0) {
        return 0;
    }

    if (i >= matSize || j >= matColSize[i]) {
        return 0;
    }

    return mat[i][j];
}

int** matrixBlockSum(int** mat, int matSize, int* matColSize, int K, int* returnSize, int** returnColumnSizes){
    int** ans = (int**)malloc(sizeof(int*) * matSize);
    *returnColumnSizes = (int*)malloc(sizeof(int) * matSize);
    int sum;
    int i,j,r,c;

    for (i = 0; i < matSize; i++) {
        ans[i] = (int*)malloc(sizeof(int) * matColSize[i]);
        (*returnColumnSizes)[i] = matColSize[i];

        for (j = 0; j < matColSize[i]; j++) {
            sum = 0;

            if (i == 0) {
                for (r = i - K; r <= i + K; r++) {
                    for (c = j - K; c <= j + K; c++) {
                        sum += getMatVal(mat, matSize, matColSize, r, c);
                    }
                }
                ans[i][j] = sum;
            } else {
                r = i - 1 - K;
                for (c = j - K; c <= j + K; c++) {
                    sum -= getMatVal(mat, matSize, matColSize, r, c);
                }
                r = i + K;
                for (c = j - K; c <= j + K; c++) {
                    sum += getMatVal(mat, matSize, matColSize, r, c);
                }

                ans[i][j] = ans[i - 1][j] + sum;
            }
        }
    }

    *returnSize = matSize;
    return ans;
}

void printMat(int** mat, int matSize, int* matColSize)
{
    printf("Mat:\n");
    for (int i = 0; i < matSize; i++) {
        for (int j = 0; j < matColSize[i]; j++) {
            printf("%d ", mat[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

void test1()
{
    int matSize = 3;
    int** mat = (int**)malloc(sizeof(int*) * matSize);
    int matColSize[] = {3, 3, 3};
    int data[][3] = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9},
    };
    for (int i = 0; i < matSize; i++) {
        mat[i] = (int*)malloc(sizeof(int) * matColSize[i]);
        for (int j = 0; j < matColSize[i]; j++) {
            mat[i][j] = data[i][j];
        }
    }

    int returnSize = 0;
    int* returnColSize = NULL;
    int** ans = matrixBlockSum(mat, matSize, matColSize, 1, &returnSize, &returnColSize);
    printMat(ans, matSize, matColSize);
}

void test2()
{
    int data[][3] = {
        {67,64,78},
        {99,98,38},
        {82,46,46},
        {6,52,55},
        {55,99,45}
    };

    int matSize = sizeof(data) / sizeof(data[0]);
    int** mat = (int**)malloc(sizeof(int*) * matSize);
    int matColSize[] = {3, 3, 3, 3, 3};
    
    for (int i = 0; i < matSize; i++) {
        mat[i] = (int*)malloc(sizeof(int) * matColSize[i]);
        for (int j = 0; j < matColSize[i]; j++) {
            mat[i][j] = data[i][j];
        }
    }

    int returnSize = 0;
    int* returnColSize = NULL;
    int** ans = matrixBlockSum(mat, matSize, matColSize, 3, &returnSize, &returnColSize);
    printMat(ans, matSize, matColSize);
}

int main()
{
    test1();
    test2();
    return 0;
}