#include <assert.h>
#include <malloc.h>
#include <string.h>
#include "mergesort.h"

void  my_memcpy(void * dest, const void * src, size_t size) {
    assert(dest != NULL);
    assert(src != NULL);
    char * copy = dest;
    const char * source = src;
    while (size > 0) {
        *copy = *source;
        size -= 1;
        copy += 1;
        source += 1;
    }
}

int mergesort(void * array, size_t elements, size_t element_size, int (*comparator)(const void*, const void*)) {
    assert(array != NULL);
    assert(comparator != NULL);
    if (elements <= 1) {
        return 0;
    }
    size_t half_elem = elements / 2;
    void * buf = malloc(element_size * half_elem);
    if (mergesort(array, half_elem, element_size, comparator) == -1 || 
        mergesort(array + half_elem * element_size, elements - half_elem, element_size, comparator) ||
        buf == NULL) {
        return -1;
    }
    my_memcpy(buf, array, half_elem * element_size);
    char * iter_array = array;
    char * array2 = array + element_size * half_elem;
    char * buf1 = buf;
    size_t index_buf = 0;
    size_t index_array2 = half_elem;
    while (index_buf < half_elem || index_array2 < elements){
        if (index_array2 != elements && (index_buf == half_elem || comparator(buf1, array2) > 0)) {
            my_memcpy(iter_array, array2, element_size);
            array2 += element_size;   
            index_array2++;
        }
        else {
            my_memcpy(iter_array, buf1, element_size);
            buf1 += element_size;
            index_buf++;
        }
        iter_array += element_size;
    }
    free(buf); 
    return 0;
}
