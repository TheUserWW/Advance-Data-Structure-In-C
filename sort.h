#ifndef SORT_H
#define SORT_H

#include <stdlib.h>
#include <stddef.h>

static void swap(void *a, void *b, size_t size) {
    char *p = a;
    char *q = b;
    while (size--) {
        char tmp = *p;
        *p++ = *q;
        *q++ = tmp;
    }
}

static size_t partition(void *base, size_t nmemb, size_t size,
                        int (*compar)(const void*, const void*)) {
    char *base_ptr = (char*)base;
    size_t pivot_index = nmemb / 2;
    char *pivot = base_ptr + pivot_index * size;
    
    swap(pivot, base_ptr + (nmemb - 1) * size, size);
    pivot = base_ptr + (nmemb - 1) * size;

    size_t store_index = 0;
    for (size_t i = 0; i < nmemb - 1; ++i) {
        if (compar(base_ptr + i * size, pivot) <= 0) {
            swap(base_ptr + i * size, base_ptr + store_index * size, size);
            store_index++;
        }
    }
    swap(base_ptr + store_index * size, pivot, size);
    return store_index;
}

static void quicksort(void *base, size_t nmemb, size_t size,
                     int (*compar)(const void*, const void*)) {
    if (nmemb <= 1) return;
    
    size_t pivot_index = partition(base, nmemb, size, compar);
    char *base_ptr = (char*)base;
    
    quicksort(base_ptr, pivot_index, size, compar);
    quicksort(base_ptr + (pivot_index + 1) * size,
             nmemb - pivot_index - 1, size, compar);
}

#define SORT_ARRAY(arr, compar) \
    quicksort((arr), sizeof(arr)/sizeof((arr)[0]), sizeof((arr)[0]), (compar))

#endif // SORT_H