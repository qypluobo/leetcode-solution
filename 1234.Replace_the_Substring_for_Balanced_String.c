#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "uthash.h"

#define Q_IDX   0
#define W_IDX   1
#define E_IDX   2
#define R_IDX   3

int getIdxByChar(char c)
{
    if (c == 'Q') {
        return Q_IDX;
    }

    if (c == 'W') {
        return W_IDX;
    }

    if (c == 'E') {
        return E_IDX;
    }

    if (c == 'R') {
        return R_IDX;
    }

    return 0;
}

int balancedString(char * s){
    int len = strlen(s);
    int ans = len;
    int target = len / 4;
    int i;
    int j;
    int k;
    int numTotal[4];
    int numExpect[4];

    memset(numTotal, 0, sizeof(numTotal));
    memset(numExpect, 0, sizeof(numExpect));

    for (i = 0; i < len; i++) {
        numTotal[getIdxByChar(s[i])] += 1;
    }

    printf("QWER: %d %d %d %d\n",
           numTotal[Q_IDX],
           numTotal[W_IDX],
           numTotal[E_IDX],
           numTotal[R_IDX]);

    if (numTotal[Q_IDX] > target) {
        numExpect[Q_IDX] = numTotal[Q_IDX] - target;
    }
    
    if (numTotal[W_IDX] > target) {
        numExpect[W_IDX] = numTotal[W_IDX] - target;
    }
    
    if (numTotal[E_IDX] > target) {
        numExpect[E_IDX] = numTotal[E_IDX] - target;
    }
    
    if (numTotal[R_IDX] > target) {
        numExpect[R_IDX] = numTotal[R_IDX] - target;
    }

    if (numExpect[Q_IDX] == 0 && numExpect[W_IDX] == 0
     && numExpect[E_IDX] == 0 && numExpect[R_IDX] == 0) {
         return 0;  // already balanced
    }

    if (numTotal[Q_IDX] == len || numTotal[W_IDX] == len
     || numTotal[E_IDX] == len || numTotal[R_IDX] == len) {
         return len - target;
    }

    for (i = 0; i < len; i++) {
        memset(numTotal, 0, sizeof(numTotal));
        for (j = i; j < len; j++) {
            numTotal[getIdxByChar(s[j])] += 1;

            if (numTotal[Q_IDX] >= numExpect[Q_IDX]
             && numTotal[W_IDX] >= numExpect[W_IDX]
             && numTotal[E_IDX] >= numExpect[E_IDX]
             && numTotal[R_IDX] >= numExpect[R_IDX]) {
                 if ((j - i + 1) < ans) {
                     ans = (j - i + 1);
                 }
                 break;
             }
        }
    }

    // i = 0;
    // j = 0;
    // memset(numTotal, 0, sizeof(numTotal));
    // while (i < len) {
        
    //     while (j < len) {
    //         numTotal[getIdxByChar(s[j])] += 1;

    //         if (numTotal[Q_IDX] >= numExpect[Q_IDX]
    //          && numTotal[W_IDX] >= numExpect[W_IDX]
    //          && numTotal[E_IDX] >= numExpect[E_IDX]
    //          && numTotal[R_IDX] >= numExpect[R_IDX]) {
    //              if ((j - i + 1) < ans) {
    //                  ans = (j - i + 1);
    //              }
    //              break;
    //          }
    //          j++;
    //     }
    //     numTotal[getIdxByChar(s[i])] -= 1;
    //     i++;
    // }

    return ans;
}

void test1()
{
    int result = balancedString("WWEQERQWQWWRWWERQWEQ");
    printf("result: %d\n", result);
}

void test2()
{
    int result = balancedString("WQWRQQQW");
    printf("result: %d\n", result);
}

int main()
{
    // test1();
    test2();
    return 0;
}