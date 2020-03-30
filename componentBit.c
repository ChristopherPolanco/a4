#include <stdlib.h>
#include <stdio.h>
#include "bitpack.h"
#include "componentBit.h"
#include "a2methods.h"
#include "uarray2.h"
#include "assert.h"
#include "arith411.h"
#include "math.h"

typedef struct floatRGB{
    float y;
    float pb;
    float pr;
} floatRGB;

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
Average* findAverage(Block* block){
    Average* average = malloc(sizeof(Average));

    //Compute the average pb and pr values
    float pbAverage = (block->one.pb + block->two.pb + block->three.pb + block->four.pb)/4.0;
    float prAverage = (block->one.pr + block->two.pr + block->three.pr + block->four.pr)/4.0;

    average->pba = pbAverage;
    average->pra = prAverage;

    return average;
}

//Helper function that checks if b, c, and d are in range
void check(float* num){
    if(*num > 0.3){
        *num = 0.3;
    }
    else if(*num < -0.3){
        *num = -0.3;
    }
    return;
}


//Helper function to do cosine transformation
BitWord* cosineTrans(Block* block, BitWord* word){
    //Get the y values
    float y1 = block->one.y;
    float y2 = block->two.y;
    float y3 = block->three.y;
    float y4 = block->four.y;

    //Perform cosine transformation
    float a = (y4 + y3 + y2 + y1)/4.0;
    float b = (y4 + y3 - y2 - y1)/4.0;
    float c = (y4 - y3 + y2 - y1)/4.0;
    float d = (y4 - y3 - y2 + y1)/4.0;

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


//Helper function that gets all the information for a BitWord
BitWord* getBitWord(Block* block, BitWord* word){
    //Gets the pr and pb average
    Average* average = findAverage(block);

    unsigned finalPba = Arith_index_of_chroma(average->pba);
    unsigned finalPra = Arith_index_of_chroma(average->pra);
    
    word = cosineTrans(block, word);

    //Add pb and pr values to the word
    word->pba = finalPba;
    word->pra = finalPra;

    free(average);

    return word;
}

uint64_t pack(BitWord* word){
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
void printOut(UArray2_T words, int width, int height){
    fprintf(stdout, "Compressed image format 2\n%u %u\n", width, height);
    for(int i = 0; i < height; i++){
        for(int j = 0; j < width; j++){
            uint64_t* temp = UArray2_at(words, j, i);
            for(int k = 3; k >= 0; k--){
                putchar(Bitpack_gets(*temp, 8, 8 * k));
            }
        }
    }
    return;
}

//Transforms component to bit
void componentToBit(UArray2_T array){
    int width = UArray2_width(array);
    int height = UArray2_height(array);

    UArray2_T words = UArray2_new(width/2, height/2, sizeof(uint64_t));

    //Keep track of position in words
    int row = 0;
    int column = 0;

    //Go through array and find the two by two blocks and turn them into code words.
    for(int i = 0; i < height; i = i + 2){
        for(int j = 0; j < width; j = j + 2){
            //allocate memory for structs
            Block* block = malloc(sizeof(Block));
            BitWord* word = malloc(sizeof(BitWord));

            floatRGB* one = UArray2_at(array, j, i);
            floatRGB* two = UArray2_at(array, j + 1, i);
            floatRGB* three = UArray2_at(array, j, i + 1);
            floatRGB* four = UArray2_at(array, j + 1, i + 1);


            block->one = *one;
            block->two = *two;
            block->three = *three;
            block->four = *four;

            word = getBitWord(block, word);

            //Turn codeword into uint64
            uint64_t codeword = pack(word);


            uint64_t* temp = UArray2_at(words, row, column); 
            *temp = codeword;


            column = column + 1;

            free(block);
            free(word);
        }
        row = row + 1;
        column = 0;
    }
    
    //Write out the array of codewords
    printOut(words, width/2, height/2);

    UArray2_free(&words);

    return;
}

/*Decompress functions-------------------------------------------------*/

