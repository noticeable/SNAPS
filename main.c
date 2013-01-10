#include <stdio.h>
#include <stdlib.h>
#include "Encoder/bmp2jpg.h"
#include "main.h"
#include "populatearray.h"
#include "sortimagearray.h"
#include "H264Decoder/parser.h"

static FRAMECHAR CurrentFrame;
static unsigned char h264buffer[h264buffersize];
static unsigned short positionarray1[5000];
static unsigned short ratingarray1[5000];
static unsigned short positionarray2[5000];
static unsigned short ratingarray2[5000];
static unsigned char verticalleft[Heights];
static unsigned char verticalright[Heights];
static unsigned char horizontaltop[Widths];
static unsigned char horizontalbottom[Widths];
static int earthdata[7];

int main(void)
{
    printf("SNAPS IMAGE PROCESSING \n");
    printf("------------------------ \n \n");
    int j;
    int images = 8;
    j = readchunk(0,&h264buffer);
    for(j=0;j<images;j++)
    {
        readimage(&CurrentFrame,j);
        //Convert to RGB and Downsample
        ratingarray1[j] = histogram(&CurrentFrame,&verticalleft,&verticalright,&horizontaltop,&horizontalbottom);
        earthfind(&verticalleft,&verticalright,&horizontaltop,&horizontalbottom, &earthdata);
        if(ratingarray1[j]>7)
        {
            ratingarray1[j] = ratingarray1[j] + circledetect(&CurrentFrame,&earthdata);
            ratingarray1[j] = ratingarray1[j] + edgedetect(&CurrentFrame);
        }
        positionarray1[j] = j;
        printf("Frame:%d, Rating:%d \n",positionarray1[j],ratingarray1[j]);
        main_encoder(2,&CurrentFrame);

    }
    printf("\n SUMMARY");
    printf("\n---------\n" );
    sortimagearray(&positionarray1,&ratingarray1,&positionarray2,&ratingarray2);
    return (0);

}





