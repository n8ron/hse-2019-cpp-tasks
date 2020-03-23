#include <malloc.h>
#include <string.h>
#include <assert.h>
#include <stdlib.h>
#include "mergesort.h"

int int_comparator(const void * a, const void * b) {
    assert(a != NULL);
    assert(b != NULL);
    return *(int*)a - *(int*)b;
}

int char_comparator(const void * a, const void * b) {
    assert(a != NULL);
    assert(b != NULL);
    return *(char*)a - *(char*)b;
}

int string_comparator(const void * first_str, const void * second_str) {
    assert(first_str != NULL);
    assert(second_str != NULL);
    return strcmp(*(const char**)first_str, *(const char**)second_str);
}

int main(int argc, char* argv[]) {
    if (argc <= 2) {
        printf("Error: incorrect input\n");
        return 0;
    }
    if (strcmp(argv[1], "int") == 0) {
        int * array = malloc(sizeof(int) * (argc - 2));
        for (int i = 0; i < argc - 2; i++) {
            array[i] = atoi(argv[i + 2]);
        }
        int failed = mergesort(array, argc - 2, sizeof(int), int_comparator);
        if (failed == -1) {
            printf("Error: memory allocation failed\n");
            free(array);
            return 1;
        }
        for (int i = 0; i < argc - 2; i++) {
            printf("%d ", array[i]);
        }
        printf("\n");
        free(array);
    } 
    else if (strcmp(argv[1], "char") == 0 ) {
        char * array = malloc(sizeof(char) * (argc - 2));
        for (int i = 0; i < argc - 2; i++) {
            array[i] = *argv[i + 2];
        }
        int failed = mergesort(array, argc - 2, sizeof(char), char_comparator);
        if (failed == -1) {
            printf("Error: memory allocation failed\n");
            free(array);
            return 1;
        }
        for (int i = 0; i < argc - 2; i++) {
            printf("%c ", array[i]);
        }
        printf("\n");
        free(array);
    }
    else if (strcmp(argv[1], "str") == 0 ) {
        char* array[argc - 2];
        for (int i = 0; i < argc - 2; i++) {
            array[i] = argv[i + 2];
        }
        int failed = mergesort(array, argc - 2, sizeof(array[0]), string_comparator);
        if (failed == -1) {
            printf("Error: memory allocation failed\n");
            return 1;
        }
        for (int i = 0; i < argc - 2; i++) {
            printf("%s ", array[i]);
        }  
        printf("\n");  
    }
}