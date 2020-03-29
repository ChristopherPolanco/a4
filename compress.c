#include "compress.h"
#include "assert.h"
#include "pnm.h"
#include "uarray2.h"
#include "a2methods.h"

#include "componentBit.h"
#include "ppmFloatConversion.h"
#include "floatrgb.h"


#define denominator 255 //RGB values to integers in the range 0 to 255

//REMEMBER TO FREE UARRAYS 
extern void compress(FILE *input){
	A2Methods_T methods = array2_methods_plain;
	assert(methods);

    //file is read and stored
    Pnm_ppm image = Pnm_ppmread(input, methods);

    //trim bounds if not even number
    if (image->width % 2 != 0){
        image->width -= 1;
    }

    if (image->height % 2 != 0){
        image->height -= 1;
    }    
    
    //convert the RGB values of each individual pixel to its corresponding Y, Pb, and Pr value.
    A2Methods_UArray2 componentParts = ppmToFloat(image);

    //convert from Y, Pb, Pr value to bit
    //output is also handled in the componentBit.h
    componentToBit(componentParts);


    Pnm_ppmfree(&image);
    methods->free(&componentParts);

    return;
}

extern void decompress(FILE *input){
    unsigned height, width;
    int read = fscanf(in, "Compressed image format 2\\n%u %u", &width, &height);
    assert(read == 2);
    int c = getc(in);
    assert(c == '\n');

    struct Pnm_ppm pixmap = { .width = width, .height = height, .denominator = denominator, .pixels = array};

    
    return;
}