#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "uthash.h"

bool isUgly(int num){
    if (num <= 0) {
        return false;
    }

    while (num != 1) {
        if (num % 2 == 0) {
            num /= 2;
        } else if (num % 3 == 0) {
            num /= 3;
        } else if (num % 5 == 0) {
            num /= 5;
        } else {
            return false;
        }
    }
    return true;
}

void test1()
{
    bool ugly = isUgly(14);
    printf("%d\n", ugly);
}

int main()
{
    test1();
    return 0;
}