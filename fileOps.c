#include <stdlib.h>
#include "assert.h"
#include "uarray2.h" 

UArray2_T readFile(FILE * fp){
    FILE* fp = fopen(argv[i], "r");
    assert(fp);

    //read in ppm image and fill a UArray2
}

void writeFile(UArray2_T uarray2){
    //use a 2d loop and write to a file

    for(int i = 0; i < y-limit; i++){
        for(int j = 0; j < x-limit; j++){

            (void) fwrite(color, 1, 3, Insert__writeFileName__here);        
        }
    }
} 


{
  const int dimx = 800, dimy = 800;
  int i, j;
  FILE *fp = fopen("first.ppm", "wb"); /* b - binary mode */
  (void) fprintf(fp, "P6\n%d %d\n255\n", dimx, dimy);
  for (j = 0; j < dimy; ++j)
  {
    for (i = 0; i < dimx; ++i)
    {
      static unsigned char color[3];
      color[0] = i % 256;  /* red */
      color[1] = j % 256;  /* green */
      color[2] = (i * j) % 256;  /* blue */
      (void) fwrite(color, 1, 3, fp);
    }
  }
  (void) fclose(fp);
  return EXIT_SUCCESS;
}