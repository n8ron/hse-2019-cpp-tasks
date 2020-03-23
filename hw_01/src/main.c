#include "bmp.h"
#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <stdlib.h>

const char * error_memory = "ERROR: Not enough memory\n";

int main(int argc, char * argv[]) {
    if (argc != 8) {
        printf("ERROR: incorrect number of arguments\n");
        return 0;
    }
    BMP_t image;
    BMP_t cropped_image;
    BMP_t rotated_cropped_image;
    int check_load = load_bmp(argv[2], &image);
    if (check_load == 1){
        return 1; 
    } 
    if (check_load == 2) {
        free_internals(&image);
        return 1;
    }
    if (init_pixels(&cropped_image, atoi(argv[6]), atoi(argv[7])) != 0) { //init cropped_image 
        printf("%s", error_memory);
        free_internals(&image);
        return 1;
    }
    if (crop(&image, &cropped_image, atoi(argv[4]), atoi(argv[5]), atoi(argv[6]), atoi(argv[7]))) {
        cropped_image.bmih.biHeight = atoi(argv[7]);
        free_internals(&cropped_image);
        free_internals(&image);
        return 1;
    }
    free_internals(&image);
    if (init_pixels(&rotated_cropped_image, atoi(argv[7]),atoi(argv[6])) != 0) {
        printf("%s", error_memory);
        free_internals(&cropped_image);
        return 1;
    }
    if (rotate(&cropped_image, &rotated_cropped_image) ||    
            save_bmp(argv[3], &rotated_cropped_image)) {
        free_internals(&cropped_image);
        free_internals(&rotated_cropped_image);
        return 1;
    }
    free_internals(&cropped_image);
    free_internals(&rotated_cropped_image);
    return 0;
}