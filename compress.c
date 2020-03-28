#include "compress.h"
#include "assert.h"
#include "pnm.h"
#include "uarray2.h"
#include "a2methods.h"


#define denominator 420 
/*Daniels said it doesn't matter as long as it doesn't pass a high number stated in the doc*/

extern void compress(FILE *input){
	A2Methods_T methods = array2_methods_plain;
	assert(methods);

    //file is read and stored
    Pnm_ppm image = Pnm_ppmread(input, methods);

    //trim if needed
    if (image->width % 2 != 0){
        image->width -= 1;
    }

    if (image->height % 2 != 0){
        image->height -= 1;
    }    
    
    //convert the RGB values of each individual pixel to its corresponding Y, Pb, and Pr value. Jenna's part don't touch
    A2Methods_UArray2 componentParts;
    //componentParts = Jenna's method
    
    //convert to codewords next



}