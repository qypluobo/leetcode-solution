#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "uthash.h"

char * longestPrefix(char * s){
    int i;
    int len = strlen(s);

    for (i= 1; i <= len - 1; i++) {
        if (0 == strncmp(s, &s[i], len - i)) {
            return s + i;
        }
    }

    return "";
}

void test1()
{
    char s[] = "level";
    char* ans = longestPrefix(s);
    printf("%s: %s\n", s, ans);
}

void test2()
{
    char s[] = "ababab";
    char* ans = longestPrefix(s);
    printf("%s: %s\n", s, ans);
}

void test3()
{
    char s[] = "leetcodeleet";
    char* ans = longestPrefix(s);
    printf("%s: %s\n", s, ans);
}

void test4()
{
    char s[] = "a";
    char* ans = longestPrefix(s);
    printf("%s: %s\n", s, ans);
}

int main()
{
    test1();
    test2();
    test3();
    test4();
    return 0;
}