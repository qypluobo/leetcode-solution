#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "uthash.h"

int romanToInt(char * s){
    int ans = 0;
    int len = strlen(s);
    int i;
    int val = 0;
    char lastState = 'A';

    for (i = 0; i < len; i++) {
        switch(s[i]) {
            case 'I':
                val = 1;
                break;
            case 'V':
                if (lastState == 'I') {
                    val = -1;
                    val += 4;
                } else {
                    val = 5;
                }
                break;
            case 'X':
                if (lastState == 'I') {
                    val = -1;
                    val += 9;
                } else {
                    val = 10;
                }
                break;
            case 'L':
                if (lastState == 'X') {
                    val = -10;
                    val += 40;
                } else {
                    val = 50;
                }
                break;
            case 'C':
                if (lastState == 'X') {
                    val = -10;
                    val += 90;
                } else {
                    val = 100;
                }
                break;
            case 'D':
                if (lastState == 'C') {
                    val = -100;
                    val += 400;
                } else {
                    val = 500;
                }
                break;
            case 'M':
                if (lastState == 'C') {
                    val = -100;
                    val += 900;
                } else {
                    val = 1000;
                }
                break;
            default:
                break;
        }
        lastState = s[i];
        ans += val;
    }

    return ans;
}

void test1()
{
    char str[] = "III";
    int ans = romanToInt(str);
    printf("%s: %d\n", str, ans);
}

void test2()
{
    char str[] = "IV";
    int ans = romanToInt(str);
    printf("%s: %d\n", str, ans);
}

void test3()
{
    char str[] = "IX";
    int ans = romanToInt(str);
    printf("%s: %d\n", str, ans);
}

void test4()
{
    char str[] = "LVIII";
    int ans = romanToInt(str);
    printf("%s: %d\n", str, ans);
}

void test5()
{
    char str[] = "MCMXCIV";
    int ans = romanToInt(str);
    printf("%s: %d\n", str, ans);
}

int main()
{
    test1();
    test2();
    test3();
    test4();
    test5();
    return 0;
}