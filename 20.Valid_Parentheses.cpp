#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "uthash.h"

bool isPair(char a, char b) 
{
    if (a == '(' && b == ')') {
        return true;
    } else if (a == '[' && b == ']') {
        return true;
    } else if (a == '{' && b == '}') {
        return true;
    } else {
        return false;
    }
}

bool isValid(char * s){
    size_t len = strlen(s);
    if (len <= 0) {
        return true;
    }

    if (len % 2) {
        return false;
    }

    char* stack = (char*)malloc(sizeof(char) * (len + 1));
    int stackTop = 0;
    char top;

    int i;
    for (i = 0; i < len; i++) {
        if (s[i] == '(' || s[i] == '[' || s[i] == '{') {
            stack[stackTop++] = s[i];
        } else if (s[i] == ')' || s[i] == ']' || s[i] == '}') {
            if (stackTop <= 0) {
                return false;
            }
            top = stack[--stackTop];
            if (isPair(top, s[i]) == false) {
                return false;
            }
        } else {
            return false;
        }
    }

    if (stackTop != 0) {
        return false;
    }
    return true;
}

void test1()
{
    char str[] = "()";
    bool ans = isValid(str);
    printf("%s: %s\n", __func__, ans ? "true" : "false");
}

void test2()
{
    char str[] = "()[]{}";
    bool ans = isValid(str);
    printf("%s: %s\n", __func__, ans ? "true" : "false");
}

void test3()
{
    char str[] = "(]";
    bool ans = isValid(str);
    printf("%s: %s\n", __func__, ans ? "true" : "false");
}

void test4()
{
    char str[] = "([)]";
    bool ans = isValid(str);
    printf("%s: %s\n", __func__, ans ? "true" : "false");
}

void test5()
{
    char str[] = "{[]}";
    bool ans = isValid(str);
    printf("%s: %s\n", __func__, ans ? "true" : "false");
}

void test6()
{
    char str[] = "[";
    bool ans = isValid(str);
    printf("%s: %s\n", __func__, ans ? "true" : "false");
}

void test7()
{
    char str[] = "()[";
    bool ans = isValid(str);
    printf("%s: %s\n", __func__, ans ? "true" : "false");
}

void test8()
{
    char str[] = "([{(";
    bool ans = isValid(str);
    printf("%s: %s\n", __func__, ans ? "true" : "false");
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
    return 0;
}