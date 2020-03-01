#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "uthash.h"

void printArray(int* data, int n)
{
    for (int i = 0; i < n; i++) {
        printf("%d ", data[i]);
    }
    printf("\n");
}

int nthUglyNumber(int n){
    int* nums = (int*)malloc(sizeof(int) * n);
    int i;
    int p2 = 0;
    int p3 = 0;
    int p5 = 0;
    int v2,v3,v5;
    int ans;

    nums[0] = 1;
    for (i = 1; i < n; i++) {
        v2 = 2 * nums[p2];
        v3 = 3 * nums[p3];
        v5 = 5 * nums[p5];

        nums[i] = v2 < v3 ? v2 : v3;
        nums[i] = nums[i] < v5 ? nums[i] : v5;

        if (nums[i] == v2) {
            p2++;
        }

        if (nums[i] == v3) {
            p3++;
        }

        if (nums[i] == v5) {
            p5++;
        }
    }

    // printArray(nums, n);

    ans = nums[n - 1];
    free(nums);
    return ans;
}

void test1()
{
    int ans = nthUglyNumber(10);
    printf("%d\n", ans);
}

void test2()
{
    int ans = nthUglyNumber(1690);
    printf("%d\n", ans);
}

int main()
{
    test1();
    test2();
    return 0;
}