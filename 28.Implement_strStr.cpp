#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "uthash.h"

#if 0
int strStr(char * haystack, char * needle){
    size_t lenH = strlen(haystack);
    size_t lenN = strlen(needle);
    int i, j;

    if (lenN == 0) {
        return 0;
    }

    if (lenH < lenN) {
        return -1;
    }

    for (i = 0; i < lenH - lenN + 1; i++) {
        for (j = 0; j < lenN; j++) {
            if (haystack[i + j] != needle[j]) {
                break;
            }
        }

        if (j == lenN) {
            return i;
        }
    }

    return -1;
}
#else
// Rabin Karp
#define PRIME_RK    16777619
#define BASE 26

long rkHash(char* s, int len)
{
    long hash = s[0] - 'a';
    int i;

    for (i = 1; i < len; i++) {
        hash = hash * BASE + (s[i] - 'a');
        hash %= PRIME_RK;
    }

    return hash;
}


int strStr(char * haystack, char * needle){
    size_t lenH = strlen(haystack);
    size_t lenN = strlen(needle);
    int i, j;
    long hashH;
    long hashN;
    long powBase = 1;

    if (lenN == 0) {
        return 0;
    }

    if (lenH < lenN) {
        return -1;
    }

    for (i = 1; i < lenN; i++) {
        powBase *= BASE;
        powBase %= PRIME_RK;
    }

    hashH = rkHash(haystack, lenN);
    hashN = rkHash(needle, lenN);
    if (hashH == hashN && 0 == strncmp(haystack, needle, lenN)) {
        return 0;
    }

    for (i = 1; i < lenH - lenN + 1; i++) {
        hashH += PRIME_RK;
        hashH -= powBase * (haystack[i - 1] - 'a');
        hashH *= BASE;
        hashH += haystack[i + lenN - 1] - 'a';
        hashH %= PRIME_RK;

        if (hashH == hashN && 0 == strncmp(&haystack[i], needle, lenN)) {
            return i;
        }
    }

    return -1;
}
#endif

void test1()
{
    char haystack[] = "hello";
    char needle[] = "ll";
    int ans = strStr(haystack, needle);
    printf("%s, %d\n", __func__, ans);
}

void test2()
{
    char haystack[] = "aaaaa";
    char needle[] = "bba";
    int ans = strStr(haystack, needle);
    printf("%s, %d\n", __func__, ans);
}

void test3()
{
    char haystack[] = "mississippi";
    char needle[] = "issi";
    int ans = strStr(haystack, needle);
    printf("%s, %d\n", __func__, ans);
}

void test4()
{
    char haystack[] = "ababcaababcaabc";
    char needle[] = "ababcaabc";
    int ans = strStr(haystack, needle);
    printf("%s, %d\n", __func__, ans);
}

int main()
{
    test1();
    test2();
    test3();
    test4();
    return 0;
}