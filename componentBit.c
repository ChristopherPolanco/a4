#include <stdlib.h>
#include <stdio.h>
#include "bitpack.h"
#include "componentBit.h"
#include "a2methods.h"
#include "uarray2.h"
#include "assert.h"
#include "floatrgb.h"


//A struct that stores the 4 pixels that are being averaged and worked on
typedef struct Block {
    floatRGB one;
    floatRGB two;
    floatRGB three;
    floatRGB four;
} Block;

//A struct that stores the average pb and pr values
typedef struct Average {
    float pba;
    float pra;
} Average;

typedef struct BitWord {
    unsigned a;
    signed b;
    signed c;
    signed d;
    unsigned pba;
    unsigned pra;
} BitWord;

//Helper function that finds the average pr and pb values
Average findAverage(Block block){
    Average average;

    //Compute the average pb and pr values
    pbAverage = (block->one->pb + block->two->pb + block->three->pb + block->four->pb)/4;
    prAverage = (block->one->pr + block->two->pr + block->three->pr + block->four->pr)/4;

    average->pba = pbAverage;
    average->pra = prAverage;

    return average
}

//Helper function to do cosine transformation
BitWord cosineTrans(Block block){
    BitWord word;

    //Get the y values
    float y1 = block->one->y;
    float y2 = block->two->y;
    float y3 = block->three->y;
    float y4 = block->four->y;

    //Perform cosine transformation
    a = (y4 + y3 + y2 + y1)/4.0;
    b = (y4 + y3 - y2 - y1)/4.0;
    c = (y4 - y3 + y2 - y1)/4.0;
    d = (y4 - y3 - y2 + y1)/4.0;

    //Check that values are in range
    check(&b);
    check(&c);
    check(&d);

    //Add a, b, c, and d to the word
    word->a = (unsigned)(roundf(a * 511));
    word->b = (signed)(roundf(b * 50));
    word->c = (signed)(roundf(c * 50));
    word->d = (signed)(roundf(d * 50));

    return word;
}

//Helper function that checks if b, c, and d are in range
void check(float * num){
    if(*num > 0.3){
        *num = 0.3;
    }
    else if(*num < -0.3){
        *num = -0.3;
    }
}

//Helper function that gets all the information for a BitWord
BitWord getBitWord(Block block){
    //Gets the pr and pb average
    Average average = findAverage(block);

    unsigned finalPba = Arith_index_of_chroma(average->pba);
    unsigned finalPbr = Arith_index_of_chroma(average->pra);

    //Gets the a, b, c, and d value
    BitWord word = cosineTrans(block);

    //Add pb and pr values to the word
    word->pba = finalPba;
    word->pra = finalPra;

    return word;
}

uint64_t pack(BitWord word){
    //Initialize codeword
    uint64_t codeword = 0;

    //Perform operations on word
    codeword = Bitpack_newu(codeword, 9, 23, word->a);
    codeword = Bitpack_news(codeword, 5, 18, word->b);
    codeword = Bitpack_news(codeword, 5, 13, word->c);
    codeword = Bitpack_news(codeword, 5, 8, word->d);
    codeword = Bitpack_newu(codeword, 4, 4, word->pba);
    codeword = Bitpack_newu(codeword, 4, 0, word->pra);

    return codeword;
}

//Helper function to write out the codewords
void printOut(A2Methods_UArray2 words){
    fprintf(stdout, "Compressed image format 2\n%u %u\n", words->width, words->height);
    for(int i = 0; i < words->height; i++){
        for(int j = 0; j < words->width; j++){
            uint64_t temp = methods->at(words, j, i);
            for(int k = 3; k >= 0; k--){
                putchar(Bitpack_gets(*temp, 8, 8 * k));
            }
        }
    }

    return;
}

//Transforms component to bit
void componentToBit(A2Methods_UArray2 array){
    A2Methods_UArray2 words = methods->new(width/2, height/2, sizeof(uint64_t));
    //Keep track of position in words
    int row = 0;
    int column = 0;
    //Go through array and find the two by two blocks and turn them into code words.
    for(int i = 0; i < array->height; i = i + 2){
        for(int j = 0; j < array->width; j = j + 2){
            //Get the block
            Block block = {.one = methods_at(array, j, i), .two = methods_at(array, j + 1, i),
                            .three = methods_at(array, j, i + 1), .four = methods_at(array, j + 1, i + 1)};
            BitWord word = getBitWord(block);

            //Turn codeword into uint64
            uint64_t codeword = pack(word);
            *methods_at(words, row, column) = codeword;
            column = column + 1;
        }
        row = row + 1;
        column = 0;
    }
    
    //Write out the array of codewords
    printOut(words);

    return;
}
