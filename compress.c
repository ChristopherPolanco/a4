#include "compress.h"
#include "assert.h"
#include "pnm.h"
#include "uarray2.h"
#include "a2methods.h"


#define denominator #### /*Daniels said it doesn't matter as long as it doesn't pass 65535, I suggest the number 42069*/
//Update, for compress image->denominator is the denominator to use 





extern void compress(FILE *input){
	A2Methods_T methods = array2_methods_plain;
	assert(methods);

    //file is read and stored
    Pnm_ppm image = Pnm_ppmread(input, methods);

    //trim if not even number
    if (image->width % 2 != 0){
        image->width -= 1;
    }

    if (image->height % 2 != 0){
        image->height -= 1;
    }    
    
    //convert the RGB values of each individual pixel to its corresponding Y, Pb, and Pr value. Jenna's part don't touch
    A2Methods_UArray2 componentParts; // = Jenna's method(image)

    //convert to codewords next
    A2Methods_UArray2 words;// = getWords(componentParts); 

    //output words
    //writeFile(words);

    //methods daniel gave us to use to convert PB and PR into 4 bit values
    //unsigned Arith_index_of_chroma(float x);

}

extern void decompress(FILE *input){
    unsigned height, width;
    int read = fscanf(in, "Compressed image format 2\\n%u %u", &width, &height);
    assert(read == 2);
    int c = getc(in);
    assert(c == '\n');

    struct Pnm_ppm pixmap = { .width = width, .height = height, .denominator = denominator, .pixels = array};
}