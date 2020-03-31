#ifndef PPMFLOATCONVERSION_INCLUDED
#define PPMFLOATCONVERSION_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include "uarray2.h"
#include "a2methods.h"
#include "pnm.h"


extern UArray2_T ppmToFloat(Pnm_ppm image, UArray2_T newArray);
extern UArray2_T floatToPpm(UArray2_T image); 

#undef T 
#endif
