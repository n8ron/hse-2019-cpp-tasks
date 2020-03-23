#include <stdint.h>
#include <stdio.h>
#pragma once
 

#define LONG int32_t
#define DWORD uint32_t
#define WORD uint16_t

#pragma pack(push, 1) 

typedef struct RGB{
    char b;
    char g;
    char r;
} RGB_t;

typedef struct BITMAPFILEHEADER {
    WORD bfType;
    DWORD bfSize;
    WORD bfReserved1;
    WORD bfReserved2;   
    DWORD bfOffBits;  
} BITMAPFILEHEADER_t;

typedef struct BITMAPINFOHEADER {
    DWORD biSize;
    LONG biWidth;
    LONG biHeight;
    WORD biPlanes;
    WORD biBitCount;
    DWORD biCompression;
    DWORD biSizeImage;
    LONG biXPelsPerMeter;
    LONG biYPelsPerMeter;
    DWORD biClrUsed;
    DWORD biClrImportant;

} BITMAPINFOHEADER_t;

#pragma pack(pop)
#pragma pack(1)  

typedef struct BMP {
    BITMAPFILEHEADER_t  bmfh;
    BITMAPINFOHEADER_t  bmih;
    RGB_t ** pixels; 
} BMP_t;

int init_pixels(BMP_t * image, int width, int height);

int load_bmp(char * filename, BMP_t * image);

int save_bmp(char * filename, BMP_t * image);
 
FILE * open_file(char * filename, char *mode);
 
int crop(BMP_t * image, BMP_t * new_image, int x, int y, int w, int h);
 
void free_internals(BMP_t * image);

int rotate(BMP_t * image, BMP_t * new_image);