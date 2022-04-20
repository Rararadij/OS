#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>

#include "lib.h"

int main() {
    printf("0 --> change library\n");
    printf("1 x --> count 'e' number\n");
    printf("2 size_of_array array --> sort array\n");

    int cmd, cur_lib = 1;
    
    // loading library
    void* handler = dlopen("lib1.so", RTLD_LAZY);
    if (!handler) {
        printf("%s\n", dlerror());
        return 1;
    }

    // resolving functions from library
    double (*e)(int);
    int* (*sort)(int*, int);
    e = dlsym(handler, "e");
    sort = dlsym(handler, "sort");
    if (dlerror() != NULL) {
        printf("%s\n", dlerror());
        return 2;
    }

    while (scanf("%d", &cmd) > 0) {
        if (cmd == 0) {
            if (dlclose(handler) < 0) {
                perror("Can't close dinamic library\n");
                return 3;
            }

            // switching libraries
            if (cur_lib == 1) {
                handler = dlopen("lib2.so", RTLD_LAZY);
                if (!handler) {
                    printf("%s\n", dlerror());
                    return 1;
                }
                cur_lib = 2;
            }
            else {
                handler = dlopen("lib1.so", RTLD_LAZY);
                if (!handler) {
                    printf("%s\n", dlerror());
                    return 1;
                }
                cur_lib = 1;
            }

            // resolving functions from library
            e = dlsym(handler, "e");
            sort = dlsym(handler, "sort");
            if (dlerror() != NULL) {
                printf("%s\n", dlerror());
                return 2;
            }

        }

        else if (cmd == 1) {
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
    dlclose(handler);
}