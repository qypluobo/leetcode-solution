#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "uthash.h"

int pow2(int n)
{
    int pow = 1;
    while (n--) {
        pow *= 2;
    }
    return pow;
}

#if 0
int kthGrammar(int N, int K){
    int size = pow2(N - 1);
    int* row = (int*)malloc(sizeof(int) * size);
    int i, j;
    int count;
    int ans;

    row[0] = 0;
    for (i = 1; i < N; i++) {
        count = pow2(i - 1);    // number size of last row

        // fill child node 
        for (j = count - 1; j >= 0; j--) {
            if (row[j] == 0) {
                row[2 * j + 1] = 1;
                row[2 * j + 0] = 0;
            } else {
                row[2 * j + 1] = 0;
                row[2 * j + 0] = 1;
            }
        }
    }

    ans = row[K - 1];
    free(row);
    return ans;
}
#else
int kthGrammar(int N, int K){
    if (N == 1) {
        return 0;
    }

    int parent = (K - 1) / 2 + 1;
    int grammar = kthGrammar(N - 1, parent);
    if (grammar == 0) {
        if ((parent - 1) * 2 + 1 == K) {
            return 0;
        } else {
            return 1;
        }
    } else {
        if ((parent - 1) * 2 + 1 == K) {
            return 1;
        } else {
            return 0;
        }
    }
}
#endif

void test1()
{
    int ans;

    ans = kthGrammar(1, 1);
    printf("%d\n", ans);
    
    ans = kthGrammar(2, 1);
    printf("%d\n", ans);

    ans = kthGrammar(2, 2);
    printf("%d\n", ans);

    ans = kthGrammar(4, 5);
    printf("%d\n", ans);

    ans = kthGrammar(30, 434991989);
    printf("%d\n", ans);
}

int main()
{
    test1();
    return 0;
}