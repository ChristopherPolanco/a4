#include <stdio.h>
#include <stdlib.h>
#include "pnm.h"
#include "uarray2.h"
#include "floatrgb.h"

#define denominator 255

A2Methods_UArray2 ppmToFloat(Pnm_ppm image){
    int width = image->width;
    int height = image->height;
    A2Methods_UArray2 newArray = methods->new(width, height, sizeof(floatRGB));
    
    //Loop through each pixel and convert each rgb value to a floating point value.
    for(int i = 0; i < height; i++){
        for(int j = 0; j < width; j++){
            Pnm_rgb pixel = image->methods->at(image->pixels, j, i);
            floatRGB newPixel = image->methods->at(newArray, j, i);
            float r = (*pixel->red)/denominator;
            float g = (*pixel->green)/denominator;
            float b = (*pixel->blue)/denominator;

            //Change the values in the new array
            float y = (0.299 * r) + (0.587 * g) + (0.114 * b);
            float pb = (-0.168736 * r) - (0.331264 * g) + (0.5 * b);
            float pr = (0.5 * r) - (0.418688 * g) - (0.081312 * b);

            *newPixel->y = y;
            *newPixel->pb = pb;
            *newPixel->pr = pr;
        }
    }
    
    return newArray;
}

U2Methods_UArray2 floatToPpm(U2Methods_UArray2 image){
    int width = originalArray->width;
    int height = originalArray->height;
    U2Methods_UArray2 newArray = methods->new(width, height, sizeof(Pnm_rgb));

    for(int i = 0; i < height; i++){
        for(int j = 0; j < width; j++){
            floatRGB pixel = methods->at(image, j, i);
            Pnm_rgb newPixel = methods->at(newArray, j, i);

            float r = (1.0 * pixel->y) + (0.0 * pixel->pb) + (1.402 * pr);
            float g = (1.0 * pixel->y) - (0.344136 * pixel->pb) - (0.714136 * pr);
            float b = (1.0 * pixel->y) + (1.772 * pixel->pb) + (0.0 * pr);

            int red = (int)(r * denominator);
            int green = (int)(g * denominator);
            int blue = (int)(b * denominator);

            *newPixel->red = red;
            *newPixel->green = green;
            *newPixel->blue = blue;
        }
    }

    return newArray;
}
