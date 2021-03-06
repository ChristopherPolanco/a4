#include "compress.h"
#include "assert.h"
#include "pnm.h"
#include "uarray2.h"
#include "a2methods.h"
#include "a2plain.h"

#include "componentBit.h"
#include "ppmFloatConversion.h"

typedef struct floatRGB{
    float y;
    float pb;
    float pr;
} floatRGB;

extern void compress(FILE *input){
    A2Methods_T methods = array2_methods_plain; 

    //read file
    Pnm_ppm image = Pnm_ppmread(input, methods);
    assert(image);

    //trim if needed
    if (image->height % 2 != 0){
        image->height -= 1;
    } 

    if (image->width % 2 != 0){
        image->width -= 1;    
    }

    UArray2_T components = UArray2_new(image->width, image->height, sizeof(floatRGB));
    assert(components);

    //Call ppmFloatConversion method to convert values
    components = ppmToFloat(image, components);

    //Converts component parts to bits
    componentToBit(components);
    printf("\n\nMade it passed componentToBit :)\n\n");


    UArray2_free(&components);
    Pnm_ppmfree(&image);

        
    return;
}


extern void decompress(FILE *input){
    unsigned height, width;
    int read = fscanf(input, "Compressed image format 2\\n%u %u", &width, &height);
    assert(read == 2);
    int c = getc(input);
    assert(c == '\n');

    int denominator = 255;

    //Pixels are NULL since array has not been given yet
    Pnm_ppm pixmap = malloc(sizeof(Pnm_ppm));
    pixmap->width = width;
    pixmap->height = height;
    pixmap->denominator = denominator;
    pixmap->pixels = NULL;
    
    bitToComponent(input, width, height, pixmap);

    return;
}
