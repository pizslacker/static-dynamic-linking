/*
 * static-dynamic-linking - main.c
 * Copyright (C) k!M/pizslacker 2026
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

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
