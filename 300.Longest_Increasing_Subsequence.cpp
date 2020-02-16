#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "uthash.h"

int max(int a, int b)
{
    return a > b ? a : b;
}

int lengthOfLIS(int* nums, int numsSize){
    if (nums == NULL || numsSize == 0) {
        return 0;
    }

    int* dp = (int*)malloc(sizeof(int) * numsSize);
    int maxLen = 0;

    dp[0] = 1;
    maxLen = 1;
    for (int i = 1; i < numsSize; i++) {
        dp[i] = 1;
        for (int j = 0; j < i; j++) {
            if (nums[i] > nums[j]) {
                dp[i] = max(dp[i], dp[j] + 1);
            }
        }
        maxLen = max(maxLen, dp[i]);
    }

    return maxLen;
}

void test1()
{
    int nums[] = {10,9,2,5,3,7,101,18};
    int res = lengthOfLIS(nums, sizeof(nums)/sizeof(nums[0]));
    printf("res: %d\n", res);
}

void test2()
{
    int nums[] = {1,3,6,7,9,4,10,5,6};
    int res = lengthOfLIS(nums, sizeof(nums)/sizeof(nums[0]));
    printf("res: %d\n", res);
}

int main()
{
    test1();
    test2();
    return 0;
}