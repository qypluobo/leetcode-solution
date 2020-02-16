#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "uthash.h"

int* countBits(int num, int* returnSize){
    int* ans = (int*)malloc(sizeof(int) * (num + 1));
    ans[0]  = 0;

    for (int i = 1; i <= num; i++) {
        if (i % 2) {
            ans[i] = ans[i - 1] + 1;
        } else {
            ans[i] = ans[i >> 1];
        }
    }
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