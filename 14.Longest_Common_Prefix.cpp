#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "uthash.h"

char * longestCommonPrefix(char ** strs, int strsSize){
    if (strsSize <= 0) {
        return strdup("");
    }

    int i, j;
    int tmpLen;
    int minLen = strlen(strs[0]);
    char cur;
    char* ans;
    bool find = false;

    for (i = 1; i < strsSize; i++) {
        tmpLen = strlen(strs[i]);
        minLen = tmpLen < minLen ? tmpLen : minLen;
    }

    if (minLen <= 0) {
        return strdup("");
    }

    for (i = 0; i < minLen; i++) {
        cur = strs[0][i];
        for (j = 1; j < strsSize; j++) {
            if (cur != strs[j][i]) {
                find = true;
                break;
            }
        }
        if (find) {
            break;
        }
    }

    ans = (char*)malloc(sizeof(char) * (i + 1));
    memset(ans, 0, sizeof(char) * (i + 1));
    strncpy(ans, strs[0], i);
    return ans;
}

void test1()
{
    char str1[] = "flower";
    char str2[] = "flow";
    char str3[] = "flight";
    char* strs[] = {
        str1, str2, str3
    };

    char* ans = longestCommonPrefix(strs, 3);
    printf("%s, %s\n", __func__, ans);
}

void test2()
{
    char str1[] = "dog";
    char str2[] = "racecar";
    char str3[] = "car";
    char* strs[] = {
        str1, str2, str3
    };

    char* ans = longestCommonPrefix(strs, 3);
    printf("%s, %s\n", __func__, ans);
}

int main()
{
    test1();
    test2();
    return 0;
}