#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "uthash.h"

char ans[5000];
char last[5000];

char * countAndSay(int n){
    if (n == 1) {
        ans[0] = '1';
        ans[1] = '\0';
        return ans;
    }

    int i, j;
    int len;
    char lastChar;
    int count;
    int offset;

    last[0] = '1';
    last[1] = '\0';
    
    for (i = 2; i <= n; i++) {
        len = strlen(last);
        count = 1;
        offset = 0;
        lastChar = last[0];
        for (j = 1; j < len; j++) {
            if (last[j] != lastChar) {
                offset += sprintf(&ans[offset], "%d%c", count, lastChar);
                lastChar = last[j];
                count = 1;
            } else {
                count++;
            }
        }
        offset += sprintf(&ans[offset], "%d%c", count, lastChar);
        ans[offset++] = '\0';

        strcpy(last, ans);
    }

    return ans;
}

void test1()
{
    char* ans;
    for (int i = 1; i <= 30; i++) {
        //printf("%d\n", i);
        ans = countAndSay(i);
        printf("%s: %02d, %s, %d\n", __func__, i, ans, strlen(ans));
    }
}

int main()
{
    test1();
    return 0;
}