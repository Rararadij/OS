#include <stdio.h>
#include <stdlib.h>

#include "lib.h"

int main() {
    printf("1 x --> count 'e' number\n");
    printf("2 size_of_array array --> sort array\n");
    int cmd;
    while (scanf("%d", &cmd) > 0) {
        if (cmd == 1) {
            int x;
            scanf("%d", &x);
            printf("%f\n", e(x));
        }
        else if (cmd == 2) {
            int size;
            scanf("%d", &size);
            int* arr = (int*)malloc(size * sizeof(int));
            for (int i = 0; i < size; ++i) {
                scanf("%d", &arr[i]);
            }
            arr = sort(arr, size);
            for (int i = 0; i < size; ++i) {
                printf("%d ", arr[i]);
            }
            printf("\n");
            free(arr);
        }
        else {
            printf("Incorrect cmd\n");
        }
    }
}