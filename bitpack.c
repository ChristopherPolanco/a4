#include <stdio.h>
#include "bitpack.h"
#include "assert.h"
#include "math.h"

#include "except.h"
Except_T Bitpack_Overflow = {"Overflow packing bits"};

bool Bitpack_fitsu(uint64_t n, unsigned width){
    //check width is in bounds
    assert(width <= 64 && width > 0);

    //check if width can accomadate n
    if((pow(2, width) - 1) < n){
        return false;
    }

    return true;
}

bool Bitpack_fitss( int64_t n, unsigned width){
    assert(width <= 64 && width > 0);

    //check if width can accomadate n
	if (n >= (- pow(2, width)) && n <= (pow(2, width) - 1)){
		return true;
	} 
		
    return false;
}

uint64_t Bitpack_getu(uint64_t word, unsigned width, unsigned lsb){
    assert((width + lsb) <= 64);

    word = word >> (64 - width);
    word = word << (64 - (width + lsb));
    return word;
}

int64_t Bitpack_gets(uint64_t word, unsigned width, unsigned lsb){
    assert((width + lsb) <= 64);

    int64_t value = word >> (64 - width);
    value = word << (64 - (width + lsb));
    return value;
}

uint64_t Bitpack_newu(uint64_t word, unsigned width, unsigned lsb, uint64_t value){
    assert(width + lsb <= 64 && width <= 64);

   if(Bitpack_fitsu(value, width) == false){
       RAISE(Bitpack_Overflow); 
   }

   uint64_t var = pow(2, width) - 1;
   var = ~(var << lsb);
   word = (word & var) | (value << (lsb));
   
   return word;
}

uint64_t Bitpack_news(uint64_t word, unsigned width, unsigned lsb,  int64_t value){
    assert(width + lsb <= 64 && width <= 64);
    
    uint64_t var = pow(2, width) - 1;

   if(Bitpack_fitss(value, width) == false){
        RAISE(Bitpack_Overflow); 
   }

   value = value & var;    
   return (Bitpack_newu(word, width, lsb, value));
}