#include <stdio.h>
#include <stdlib.h>
#include "math_lib.h"

int main() {
    size_t size = 5000000; // 5 million
    long long *arr = malloc(size * sizeof(long long));
    
    if (!arr) return 1;
    for(size_t i = 0; i < size; i++) arr[i] = 1;

    printf("Sum result: %lld\n", sum_array(arr, size));

    free(arr);
    return 0;
}