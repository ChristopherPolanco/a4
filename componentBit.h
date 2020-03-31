#ifndef COMPONENTBIT_INCLUDED
#define COMPONENTBIT_INCLUDED

#include <stdlib.h>
#include <stdio.h>
#include "bitpack.h"
#include "componentBit.h"
#include "a2methods.h"
#include "uarray2.h"
#include "assert.h"
#include "arith411.h"
#include "pnm.h"

extern void componentToBit(UArray2_T array);
extern void bitToComponent(FILE* fp, unsigned int width, unsigned int height, Pnm_ppm pixmap);

#undef T
#endif
