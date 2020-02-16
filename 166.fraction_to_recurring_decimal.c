#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "uthash.h"

#define BUFFER_SIZE     100000

struct MyHashNode {
    int key;
    int val;
    UT_hash_handle hh;
};

char * fractionToDecimal(int numerator, int denominator){
    char* ans = (char*)malloc(sizeof(char) * BUFFER_SIZE);
    int index = 0;

    long long nm = llabs((long long)numerator);
    long long dm = llabs((long long)denominator);

    long long  remain = 0;
    long long  frac = 0;
    int i = 0;

    struct MyHashNode* hashTable = NULL;
    int key = 0;
    struct MyHashNode* tmp = NULL;
    struct MyHashNode* curItem = NULL;

    memset(ans, 0, sizeof(char) * BUFFER_SIZE);

    if  ((numerator > 0 && denominator < 0) || (numerator < 0 && denominator > 0)) {
        ans[index++] = '-';
    }

    frac = nm / dm;
    remain = nm % dm;
    sprintf(&ans[index], "%lld", frac);
    if (remain == 0) {
        return ans;
    }

    index = strlen(ans);
    ans[index++] = '.';

    while (remain)  {
        HASH_FIND_INT(hashTable, &remain, tmp);
        if (tmp != NULL) {
            ans[index] = ')';
            for (i = index; i >= tmp->val; i--) {
                ans[i + 1] = ans[i];
            }
            ans[tmp->val] = '(';
            index++;
            break;
        }

        tmp = (struct MyHashNode*)malloc(sizeof(struct MyHashNode));
        tmp->key = remain;
        tmp->val = index;
        HASH_ADD_INT(hashTable, key, tmp);

        remain *= 10;
        ans[index++] = remain / dm + '0';
        remain %= dm;
    }

    HASH_ITER(hh, hashTable, curItem, tmp) {
        HASH_DEL(hashTable, curItem);
        free(curItem);
    }

    return ans;
}

void test1()
{
    char* ans =  fractionToDecimal(1, 2);
    printf("ans: %s\n", ans);
}

void test2()
{
    char* ans =  fractionToDecimal(4, 9);
    printf("ans: %s\n", ans);
}

void test3()
{
    char* ans =  fractionToDecimal(20, 4);
    printf("ans: %s\n", ans);
}

void test4()
{
    char* ans =  fractionToDecimal(4, 333);
    printf("ans: %s\n", ans);
}

void test5()
{
    char* ans =  fractionToDecimal(1, 214748364);
    printf("ans: %s\n", ans);
}

void test6()
{
    char* ans =  fractionToDecimal(-50, 8);
    printf("ans: %s\n", ans);
}

void test7()
{
    char* ans =  fractionToDecimal(-1, -2147483648);
    printf("ans: %s\n", ans);
}

void test8()
{
    char* ans =  fractionToDecimal(-2147483648, 1);
    printf("ans: %s\n", ans);
}

void test9()
{
    char* ans =  fractionToDecimal(-2147483648, -1999);
    printf("ans: %s\n", ans);
}

int main()
{
    test1();
    test2();
    test3();
    test4();
    test5();
    test6();
    test7();
    test8();
    test9();
    return 0;
}