#include <stdio.h>
#include <stdlib.h>
#include "pnm.h"
#include "uarray2.h"

#define denominator 255


typedef struct floatRGB{
    float y;
    float pb;
    float pr;
} floatRGB;


UArray2_T ppmToFloat(Pnm_ppm image, UArray2_T newArray){
    int width = image->width;
    int height = image->height;
    
    //Loop through each pixel and convert each rgb value to a floating point value.
    for(int i = 0; i < height; i++){
        for(int j = 0; j < width; j++){
            Pnm_rgb pixel = image->methods->at(image->pixels, j, i);
            floatRGB* newPixel = UArray2_at(newArray, j, i);
            float r = (pixel->red)/denominator;
            float g = (pixel->green)/denominator;
            float b = (pixel->blue)/denominator;

            //Change the values in the new array
            float y = (0.299 * r) + (0.587 * g) + (0.114 * b);
            float pb = (-0.168736 * r) - (0.331264 * g) + (0.5 * b);
            float pr = (0.5 * r) - (0.418688 * g) - (0.081312 * b);

            newPixel->y = y;
            newPixel->pb = pb;
            newPixel->pr = pr;
        }
    }   
    return newArray;
}


void check2(float* value){
    if(*value < 0.0) *value = 0.0;
    if(*value > 1.0) *value = 1.0;

    return;
}


UArray2_T floatToPpm(UArray2_T image){
    int width = UArray2_width(image);
    int height = UArray2_height(image);
    UArray2_T newArray = UArray2_new(width, height, sizeof(Pnm_rgb));

    for(int i = 0; i < height; i++){
        for(int j = 0; j < width; j++){
            floatRGB* pixel = UArray2_at(image, j, i);
            Pnm_rgb newPixel = UArray2_at(newArray, j, i);

            float r = (1.0 * pixel->y) + (0.0 * pixel->pb) + (1.402 * pixel->pr);
            float g = (1.0 * pixel->y) - (0.344136 * pixel->pb) - (0.714136 * pixel->pr);
            float b = (1.0 * pixel->y) + (1.772 * pixel->pb) + (0.0 * pixel->pr);

            check2(&r);
            check2(&g);
            check2(&b);

            int red = (int)(r * denominator);
            int green = (int)(g * denominator);
            int blue = (int)(b * denominator);

            newPixel->red = red;
            newPixel->green = green;
            newPixel->blue = blue;
        }
    }

    return newArray;
}
