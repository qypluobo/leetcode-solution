#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "uthash.h"

#if 0
int cmpInt(const void* a, const void* b)
{
    if (*(const int*)a < *(const int*)b) {
        return -1;
    } else if (*(const int*)a == *(const int*)b) {
        return 0;
    } else {
        return 1;
    }
}

int longestConsecutive(int* nums, int numsSize){
    if (nums == NULL || numsSize == 0) {
        return 0;
    }

    if (numsSize == 1) {
        return 1;
    }

    int j;
    int length;
    int ans = 0;

    qsort(nums, numsSize, sizeof(int), cmpInt);

    j = 1;
    while (j < numsSize) {
        length = 1;
        while (j < numsSize) {
            if ((nums[j] - nums[j - 1]) == 1) {
                length++;
            } else if (nums[j] - nums[j - 1] > 1) {
                break;
            }

            ans = length > ans ? length : ans;
            j++;
        }

        j += 1;
    }

    return ans;
}
#else
int longestConsecutive(int* nums, int numsSize){
    if (nums == NULL || numsSize == 0) {
        return 0;
    }

    if (numsSize == 1) {
        return 1;
    }

    int ans;
}
#endif

void test1()
{
    int nums[] = {100, 4, 200, 1, 3, 2};
    int ans = longestConsecutive(nums, sizeof(nums)/sizeof(nums[0]));
    printf("%d\n", ans);
}

void test2()
{
    int nums[] = {9,1,4,7,3,-1,0,5,8,-1,6};
    int ans = longestConsecutive(nums, sizeof(nums)/sizeof(nums[0]));
    printf("%d\n", ans);
}

int main()
{
    test1();
    test2();
    return 0;
}