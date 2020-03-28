#include <stdio.h>

/* The two functions below are functions you should implement.
   They should take their input from the parameter and should
   write their output to stdout */

extern void compress(FILE *input); // reads PPM and writes a compressed image
   //trim method goes here to round out image size
   //convert the RGB values of each individual pixel to its corresponding Y, Pb, and Pr value. Returns the converted values in Uarray2. JENNA'S PART 
   //compress and make code words
   //output code words (handle out put in the .c)


extern void decompress(FILE *input); // reads a compressed image and writes PPM
