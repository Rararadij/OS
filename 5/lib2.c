#include <stdio.h>


// counting 'e' number
double e(int x) {
    printf("Counting 'e' number using Taylor series\n");
    double ans = 0;
    long long factorial = 1;
    for (int n = 0; n <= x; ++n) {
        if (n != 0) {
            factorial *= n;
        }
        ans += 1. / factorial;
    }
    return ans;
}

// quick sort
void quick_sort(int* arr, int l, int r) {
    int m = arr[(l + r) / 2], i = l, j = r;
    while (i <= j) {
        while (arr[i] < m) {
            ++i;
        }
        while (arr[j] > m) {
            --j;
        }
        if (i <= j) {
            int tmp = arr[i];
            arr[i] = arr[j];
            arr[j] = tmp;
            ++i;
            --j;
        }
    }
    if (l < j) {
        quick_sort(arr, l, j);
    }
    if (i < r) {
        quick_sort(arr, i, r);
    }
}

int* sort(int* arr, int n) {
    printf("Sorting an array usuing quick sort\n");
    quick_sort(arr, 0, n - 1);
    return arr;
}