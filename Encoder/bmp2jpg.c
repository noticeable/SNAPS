#include <stdio.h>
#include <stdlib.h>
#include "ejpgl.h"
#include "bmp2jpg.h"
#include "ColorConversion.h"
#include "dct.h"
#include "huffman.h"
#include "jpeg.h"
#include "zzq.h"

JPEGHEADER _jpegheader;

FILE *infile, *outfile;
static unsigned char buffer[MACRO_BLOCK_SIZE*3];
signed char pixelmatrix[MACRO_BLOCK_SIZE][MACRO_BLOCK_SIZE*3];
signed char YMatrix[MATRIX_SIZE][MATRIX_SIZE];
signed char CrMatrix[MATRIX_SIZE][MATRIX_SIZE];
signed char CbMatrix[MATRIX_SIZE][MATRIX_SIZE];

void writejpegfooter()
{
       unsigned char footer[2];
       footer[0] = 0xff;
       footer[1] = 0xd9;
       fwrite(footer,sizeof(footer),1,outfile);
	return;

}

int openBMPJPG(int position)
{

	int jpegheadersize;
    char filename[10];
    sprintf(filename,"SDCard/Images/%d.jpg",position);
  	outfile = fopen(filename,"wb");
  	if (outfile == NULL)
        {
          	printf("Error Saving File");
		exit(0);
  	}


    	jpegheadersize = writejpegheader(&_jpegheader);
	if (jpegheadersize == 0) {
       	printf("\nerror in writing jpg header");
		exit(0);
		}

    	fwrite(&_jpegheader,jpegheadersize,1,outfile);

  	return 1;

}


int closeBMPJPG() {
        printf("Encoding Success! \n \n");
     	writejpegfooter();
        fclose(outfile);
        fclose(infile);
	 return 0;

}

void put_char(unsigned char c) {

	fwrite(&c, 1, 1, outfile);

}


int main_encoder(int argc, FRAMECHAR *CurrentFrame)
{

    int compression,sample;
    unsigned int col, cols, row, rows, framenumber,row2, col2;
    framenumber = CurrentFrame->position;
    openBMPJPG(framenumber);
    rows = CurrentFrame->height/MACRO_BLOCK_SIZE;
    cols = CurrentFrame->width/MACRO_BLOCK_SIZE;
    dct_init_start();
    zzq_encode_init_start(compression);
    vlc_init_start();

       for (row = 0; row < rows; row++)
       {
      		for (col = 0; col < cols; col++)
      		{
                for(row2 = 0;row2<MACRO_BLOCK_SIZE;row2++)
                {
                        for(col2 = 0;col2<MACRO_BLOCK_SIZE*3;col2++)
                        {
                            pixelmatrix[row2][col2] = CurrentFrame->framebits[row*MACRO_BLOCK_SIZE+row2][col*MACRO_BLOCK_SIZE*3+col2]-128;
                        }
                }
                for(sample=0;sample<5;sample++)
                {
                    if(sample<4)
                     {
                        RGB2YCrCb(pixelmatrix,YMatrix,CrMatrix,CbMatrix,sample);
                        dct(YMatrix,0);
                      }
                      else
                      {
                        dct(CrMatrix,1);
                        dct(CbMatrix,2);
                      }
                }
            }
        }

	dct_stop_done();
	zzq_encode_stop_done();
	vlc_stop_done();

	closeBMPJPG();
	return 0;

}


