#include <stdio.h>
#include <math.h>

#include "lib.h"


// counting 'e' number
double e(int x) {
    printf("Counting 'e' number using second remarkable limit\n");
    return pow(1 + 1. / x, x);
}

// bubble sort
int* sort(int* arr, int n) {
    printf("Sorting an array usuing bubble sort\n");
    for (int i = 0; i < n - 1; ++i) {
        for (int j = i; j < n; ++j) {
            if (arr[i] > arr[j]) {
                int tmp = arr[i];
                arr[i] = arr[j];
                arr[j] = tmp;
            }
        }
    }
    return arr;
}