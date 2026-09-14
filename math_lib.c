#include "math_lib.h"

// A massive 5MB dummy array embedded in the library
const char massive_dummy_data[5000000] = {1}; 

long long sum_array(const long long *arr, size_t size) {
    long long sum = 0;
    for (size_t i = 0; i < size; i++) {
        sum += arr[i];
    }
    return sum;
}