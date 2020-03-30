#ifndef PPMFLOATCONVERSION_INCLUDED
#define PPMFLOATCONVERSION_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include "uarray2.h"
#include "a2methods.h"

extern A2Methods_Array2 ppmToFloat(Pnm_ppm image);
extern A2Methods_Array2 floatToPpm(A2Methods_Array2 image); 

#undef T 
#endif
