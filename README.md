# a4

Christopher Polanco && Jenna Bouchard

CSC 411 Assignment 4

Due: 3/30/2020

– Acknowledges help you may have received from or collaborative work you may have undertaken with others.
We recieved no assistance on this assignment.


– Identifies what has been correctly implemented and what has not
Compression is fully functional. All helper functions used perform as they are meant to. 
Bitpack is fully functional.
Decompression is tbd.


– Explains the architecture of your solution
    With the image.c provided by the professor the user can either compress or decompress an image.

    Compress:
        -Reads file into a Pnm_ppm image file.
        -Trims image if it is an odd number.
        -To convert RGB into component parts (y, pb, pr), we call the funcion ppmToFloat() available in ppmFloatConversion.h. This retruns a UArray to of component parts.
        -To convert components to bits, we call the funcion componentToBit() and provide it a UArray2 comprised of component parts. This function is available in    
        componentBit.h. This .h file also handles output of compression.

    Decompress:
        -This function sets up the pixmap struct and calls bitToComponent().
        -We rely on componentBit.c and bitToComponent() to perform decompression.


    ppmFloatConversion:
        -Contains two funcions, 
        extern UArray2_T ppmToFloat(Pnm_ppm image, UArray2_T newArray);
        extern UArray2_T floatToPpm(UArray2_T image); 

        -ppmToFloat() is called during compression in order to convert RGB into Y, Pb, Pr values.
        -floatToPpm() is called during decompression in order to convert Y, Pb, Pr vaules into RGB.


    componentBit:
        -Contains two funcions,
            extern void componentToBit(UArray2_T array);
            extern void bitToComponent(FILE* fp, unsigned int width, unsigned int height, Pnm_ppm pixmap);

        componentToBit()
            Is called during compression. This funcion and its helper funcions take a UArray2 of component parts and turn it into bits. Then outputs the results. 

        bitToComponent()
            Is called during decompression. Most of decompression is done through this funcion. It converts bits to component parts with its helper functions. From this function it calls floatToPpm() in order to convert component parts to RGB. Lastly it outputs results.


– Says approximately how many hours you have spent analyzing the problems posed in the assignment
    My partner and I spent an estimated 4 or 5 hours analyzing the problems and planning how we are going to implement our solution.

– Says approximately how many hours you have spent solving the problems after your analysis
    We spent roughly 35 hours implementing our solution.