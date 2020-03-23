#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "point_list.h"
#include "clist.h"

void my_counter(intrusive_node * node, void * data) {
    assert(node != NULL);
    assert(data != NULL);
    *(int*)data+= 1;
}

void my_write_bin(int x, void * output_f) {
    unsigned char c;
    for (int i = 0; i < 3; i++) {
        c = x;
        fwrite(&c, sizeof(char), 1, output_f);
        x = x >> 8;
    }
}

void my_save_bin(intrusive_node * node, void * output_f) {
    assert(node != NULL);
    assert(output_f != NULL);
    point_node * point =  get_point(node);
    my_write_bin(point->x, output_f);
    my_write_bin(point->y, output_f);
}

void my_load_text(intrusive_list * list, void * input) {
    assert(list != NULL);
    assert(input != NULL);
    int x;
    int y;
    FILE* in = fopen(input, "r");
    while (fscanf(in, "%d %d", &x, &y) >= 0) {
        add_point(list, x, y);
   }  
   fclose(in);
}

void my_load_bin(intrusive_list * list, void * input) {
    assert(list != NULL);
    assert(input != NULL);
    int x;
    int y;
    FILE* in = fopen(input, "rb");
    unsigned char buf[6];
    while (fread(buf, sizeof(char), 6, in) == 6) {
        x = buf[0] + 256 * buf[1] + 256 * 256 * buf[2];
        y = buf[3] + 256 * buf[4] + 256 * 256 * buf[5];
        add_point(list, x, y);
    }
    fclose(in);
}

void my_save_text(intrusive_node * node, void * output_f) {
    assert(node != NULL);
    assert(output_f != NULL);
    point_node * point =  get_point(node);
    fprintf(output_f, "%d %d\n", point->x, point->y);
}

void my_print(intrusive_node * node, void * format) {
    assert(node != NULL);
    assert(format != NULL);
    point_node * point  =  get_point(node);
    printf(format, point->x, point->y);  
} 


int main(int argc, char* argv[]) {
    intrusive_list list;
    intrusive_list * l = &list;
    if (argc <= 2) {
        return 0;
    }
    int numb = 0;
    int * count = &numb;
    init_list(l);
    if (strcmp(argv[1], "loadtext") == 0) {
        my_load_text(l, argv[2]);
    }
    else {
        my_load_bin(l, argv[2]);
    }   
    if (strcmp(argv[3], "savetext") == 0) {
        FILE* out = fopen(argv[4], "w");
        apply(l, my_save_text, out);  
        fclose(out);
    }
    else if (strcmp(argv[3], "savebin") == 0) {
        FILE* out = fopen(argv[4], "wb");
        apply(l, my_save_bin, out);
        fclose(out);
    }
    else if (strcmp(argv[3], "print") == 0 ){
        apply(l, my_print, argv[4]);
        printf("\n"); 
    }
    else {
        *count = 0;
        apply(l, my_counter, count);
        printf("%d\n", *count);
    }
    remove_all_points(l);
    return 0;
}