#ifndef PPMFLOATCONVERSION_INCLUDED
#define PPMFLOATCONVERSION_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include "uarray2.h"
#include "a2methods.h"

extern A2Methods_UArray2 ppmToFloat(Pnm_ppm image);
extern U2Methods_UArray2 floatToPpm(U2Methods_UArray2 image); 

#undef T 
#endif
