//word part

struct Uncoded_Values{
    double a;
    double b;
    double c;
    double d;
    double pr;
    double pb;
};

struct Coded_Values{ 
    int a;
    int b;
    int c;
    int d;
    unsigned int pr; //unsigned because of quantize function
    unsigned int pb;
};

For coding b, c, and d, your objective is to code the floating-point interval [−0.3, +0.3] 

extern A2Methods_UArray2 color_to_uncoded_values(A2Methods_UArray2 
                color_space_array){
    A2Methods_T methods = uarray2_methods_plain;
    int width = methods->width(color_space_array);
    int height = methods->height(color_space_array);
    A2Methods_UArray2 uncoded_values_array = methods->new(width/2, height/2, 
        sizeof(struct Uncoded_Values));
    CS_values *  y1, * y2, * y3, * y4;
    uncoded_values * temp_uncoded; 
    for(int j = 0; j < height; j+=2){
        for(int i = 0; i < width; i+=2){
            
            temp_uncoded = methods->at(uncoded_values_array, i/2, j/2);
            y1 = methods->at(color_space_array, i, j); //Y1
            y2 = methods->at(color_space_array, i+1, j); //Y2
            y3 = methods->at(color_space_array, i, j+1); //Y3
            y4 = methods->at(color_space_array, i+1, j+1); //Y4
            temp_uncoded->a = (y4->y + y3->y + y2->y + y1->y)/4.0;
            temp_uncoded->b = (y4->y + y3->y - y2->y - y1->y)/4.0;
            temp_uncoded->c = (y4->y - y3->y + y2->y - y1->y)/4.0;
            temp_uncoded->d = (y4->y - y3->y - y2->y + y1->y)/4.0;
            temp_uncoded->pr = (y4->pr + y3->pr + y2->pr + y1->pr)/4.0;
            temp_uncoded->pb = (y4->pb + y3->pb + y2->pb + y1->pb)/4.0;
            if(temp_uncoded->a < 0)
               temp_uncoded->a = 0;
            if(temp_uncoded->a > 1)
               temp_uncoded->a = 1;
            if(temp_uncoded->b > 0.3)
                temp_uncoded->b = 0.3;
            if(temp_uncoded->b < -0.3)
                temp_uncoded->b = -0.3;
            if(temp_uncoded->c > 0.3)
                temp_uncoded->c = 0.3;
            if(temp_uncoded->c < -0.3)
                temp_uncoded->c = -0.3;
            if(temp_uncoded->d > 0.3)
                temp_uncoded->d = 0.3;
            if(temp_uncoded->d < -0.3)
                temp_uncoded->d = -0.3; 
        }
    }
    return uncoded_values_array;
}

//Component - code the a, b, c, d, Pb, and Pr values.

extern A2Methods_UArray2 code_values(A2Methods_UArray2 uncoded_values_array){
    A2Methods_T methods = uarray2_methods_plain;
    int width = methods->width(uncoded_values_array);
    int height = methods->height(uncoded_values_array);
    A2Methods_UArray2 coded_values_array = methods->new(width, height, 
        sizeof(struct Coded_Values));
    coded_values * temp_coded;
    uncoded_values * temp_uncoded;
    double a, b, c, d;
    for(int j = 0; j < height; j++){
        for(int i = 0; i < width; i++){
            temp_coded = methods->at(coded_values_array, i, j);
            temp_uncoded = methods->at(uncoded_values_array, i, j);
            a = temp_uncoded->a;
            b = temp_uncoded->b;
            c = temp_uncoded->c;
            d = temp_uncoded->d;
            if(a > 1.0)
                a = 1.0;
            if(a < 0)
                a = 0;
            if(b > 0.3)
                b = 0.3;
            if(b < -0.3)
                b = -0.3;
            if(c > 0.3)
                c = 0.3;
            if(c < -0.3)
                c = -0.3;
            if(d > 0.3)
                d = 0.3;
            if(d < -0.3)
                d = -0.3;
            temp_coded->a = round((a*511));
            temp_coded->b = round((b*50.0));
            temp_coded->c = round((c*50.0));
            temp_coded->d = round((d*50.0));
            temp_coded->pb = Arith40_index_of_chroma(temp_uncoded->pb);
            temp_coded->pr = Arith40_index_of_chroma(temp_uncoded->pr);
        }
    }        
    return coded_values_array;
}