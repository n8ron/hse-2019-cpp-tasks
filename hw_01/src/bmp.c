#include "bmp.h"
#include <malloc.h>
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

extern const char * error_memory;

int init_pixels(BMP_t * image, int width, int height) {
    image->pixels = malloc(sizeof(int *) * height);
    if (image->pixels == NULL) {
        return 1;
    }
    for (int i = 0; i < height; ++i) {
        image->pixels[i] = malloc(width * sizeof(RGB_t));
        if (image->pixels[i] == NULL) {
            for (size_t j = 0; j < (size_t)i; j++) {
                free(image->pixels[j]);
            }
            free(image->pixels);
            return 1;
        }
    }
    return 0;
}

int load_bmp(char * file_name, BMP_t * image) {
    assert(image != NULL);  
    assert(file_name != NULL);
    FILE * input = open_file(file_name, "rb");
    if (input == NULL) {
        return 1; // 1 = not init
    }
    if (fread(&image->bmfh, 14, 1, input) != 1) {
        printf("ERROR: Incorrect input\n");
        fclose(input);
        return 1;    
    }
    if (fread(&image->bmih, 40, 1, input) != 1) {
        printf("ERROR: Incorrect input\n");
        fclose(input);
        return 1;   
    } 
    int height = image->bmih.biHeight;
    int width = image->bmih.biWidth;
    int extra = (4 - (sizeof(RGB_t) * width) % 4) % 4;
    char * tmp = malloc(4 * sizeof(char));
    if (tmp == NULL) {
        printf("%s", error_memory);
        return 1;
    }
    if (init_pixels(image, width, height) != 0) { 
        free(tmp);
        printf("%s", error_memory);
        return 1;
    }
    //image is init, now exit code = 2
    for(int i = 0; i < height; i++){
        if ((int)fread(image->pixels[height - i - 1], sizeof(RGB_t), width, input) != width){
            free(tmp);
            printf("ERROR: Incorrect input\n");
            fclose(input);
            return 2;
        } 
        if ((int)fread(tmp, sizeof(char), extra, input) != extra){
            free(tmp);
            printf("ERROR: Incorrect input\n");
            fclose(input);
            return 2;
        }   
    }
    free(tmp);
    fclose(input);
    return 0;
}
 
int save_bmp(char * file_name, BMP_t * image) {
    assert(image != NULL);
    assert(file_name != NULL);
    FILE * output = open_file(file_name, "wb");
    int height = image->bmih.biHeight;
    int width = image->bmih.biWidth;
    if (fwrite(&image->bmfh, sizeof(image->bmfh), 1, output) != 1) {
        printf("%s\n", error_memory);
        fclose(output);
        return 1;
    }
    if (fwrite(&image->bmih, sizeof(image->bmih), 1, output) != 1) {
        printf("%s\n", error_memory);
        fclose(output);
        return 1;
    }
    int zero = 0;
    int extra = (4 - (sizeof(RGB_t) * width) % 4) % 4;
    for(int i = 0; i < height; i++){
        if (fwrite(image->pixels[height - i - 1], sizeof(RGB_t) * width, 1, output) != 1) {
            printf("%s\n",error_memory);
            fclose(output);
            return 1;
        }
        if (fwrite(&zero, 1, extra, output) != (size_t)extra) {
            printf("%s\n",error_memory);
            fclose(output);
            return 1;
        }
    }
    fclose(output);
    return 0;
}
 
FILE * open_file(char * file_name, char * mode) {
    assert(file_name != NULL);
    assert(mode != NULL);   
    FILE * f = fopen(file_name, mode);
    if (f == NULL) {
        printf("Cannot open file %s", file_name);
        return NULL;
    }
    return f;
}
 
void free_internals(BMP_t * image) {
    assert(image != NULL);
    for (size_t i = 0; i < ((size_t)image->bmih.biHeight); i++) {
        free(image->pixels[i]);
    }
    free(image->pixels);
}

int crop(BMP_t * image, BMP_t * cropped_image, int x, int y, int w, int h) {
    assert(image != NULL);
    assert(cropped_image != NULL);
    if (!((0 <= x + w) && (x + w <= image->bmih.biWidth) &&
        (0 <= y + h)  && (y + h <= image->bmih.biHeight))) {
        printf("ERROR: Incorrect size\n");
        return 1;
    }
    int height = image->bmih.biHeight;
    int width = image->bmih.biWidth;
    cropped_image->bmih = image->bmih;
    cropped_image->bmfh = image->bmfh;
    cropped_image->bmfh.bfSize -= sizeof(RGB_t) * (height * width - w * h);
    cropped_image->bmih.biWidth = w;
    cropped_image->bmih.biSizeImage = sizeof(RGB_t) * (w * h);
    cropped_image->bmih.biHeight = h;
    int extra = (4 - (sizeof(char) * w) % 4) % 4; 
    cropped_image->bmfh.bfSize += extra * h * sizeof(char);
    cropped_image->bmih.biSizeImage += extra * h * sizeof(char);
    for (int i = 0; i < h; i++) {
        for (int j = 0; j < w; j++) {
            cropped_image->pixels[i][j] = image->pixels[i + y][j + x];
        }
    } 
    return 0;
}

int rotate(BMP_t * cropped_image, BMP_t * rotated_cropped_image) {
    assert(cropped_image != NULL);
    assert(rotated_cropped_image != NULL);
    int height = cropped_image->bmih.biHeight;
    int width = cropped_image->bmih.biWidth;
    rotated_cropped_image->bmih = cropped_image->bmih;
    rotated_cropped_image->bmfh = cropped_image->bmfh;
    int extra = (4 - (sizeof(char) * width) % 4) % 4; 
    rotated_cropped_image->bmfh.bfSize -= extra * height * sizeof(char);
    rotated_cropped_image->bmih.biSizeImage -= extra * height * sizeof(char);
    extra = (4 - (sizeof(char) * height) % 4) % 4; 
    rotated_cropped_image->bmfh.bfSize += extra * width * sizeof(char);
    rotated_cropped_image->bmih.biSizeImage += extra * width * sizeof(char);
    rotated_cropped_image->bmih.biWidth = height;
    rotated_cropped_image->bmih.biHeight = width;
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            rotated_cropped_image->pixels[j][height-i-1] = cropped_image->pixels[i][j];
        }
    }
    return 0;
}
