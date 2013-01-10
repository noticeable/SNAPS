#include "main.h"
#include "earthfind.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void earthfind(unsigned char *verticalleft, unsigned char *verticalright, unsigned char *horizontalbottom,unsigned char *horizontaltop, int *earthdata)
{
    int i,j;
    int slopevl,slopevr,slopeht,slopehb;
    int slopevlfound, slopevrfound, slopehtfound, slopehbfound;
    int foundvltop, foundvrtop, foundhtleft, foundhbleft;
    int foundvl, foundvr, foundht, foundhb;
    foundvltop = 0;
    foundvrtop = 0;
    foundhtleft = 0;
    foundhbleft = 0;
    foundvl = 0;
    foundvr = 0;
    foundht = 0;
    foundhb = 0;

    for(j=0;j<8;j++)
    {
        earthdata[j] = 0;
    }

    for(i=0;i<Heights-3;i++)
    {

        slopevl=(verticalleft[i+3]-verticalleft[i])/3;
        slopevr=(verticalright[i+3]-verticalright[i])/3;

        if(slopevl < 0 && verticalleft[i]>140 && foundvltop <2) //Left Earth on Top of Picture
        {
            foundvltop = 1;
            foundvl = 1;
            earthdata[0] = i;
            earthdata[1] = -1;
        }
        if(slopevl > 0 && verticalleft[i]>140 && foundvl == 0 && i>5)  //Left Earth on Bottom of Picture
        {
            foundvl = 1;
            foundvltop = 2;
            earthdata[0] = i;
            earthdata[1] = 1;
        }

         if(slopevr < 0 && verticalright[i]>140 && foundvrtop <2)   //Right Earth on Top of Picture
        {
            foundvrtop = 1;
            foundvr = 1;
            earthdata[2] = i;
            earthdata[3] = -1;
        }
        if(slopevr > 0 && verticalright[i]>140 && foundvr == 0 && i>5)  //Right Earth on Bottom of Picture
        {
            foundvr = 1;
            foundvrtop = 2;
            earthdata[2] = i;
            earthdata[3] = 1;
        }

    }

    for(i=0;i<Widths-3;i++)
    {

        slopeht=(horizontaltop[i+3]-horizontaltop[i])/3;
        slopehb=(horizontalbottom[i+3]-horizontalbottom[i])/3;
        //printf(" %d \n",horizontaltop[i+3]);

        if(slopeht > 0 && horizontaltop[i]>170 && foundht == 0)  //Top Earth on right of Picture
        {
            foundht = 1;
            foundhtleft = 2;
            earthdata[4] = i;
            earthdata[5] = 1;
        }
        if(slopeht < 0 && horizontaltop[i]>170 && foundhtleft < 2) //Top Earth on Top of Picture
        {
            foundhtleft = 1;
            foundht = 1;
            earthdata[4] = i;
            earthdata[5] =  -1;
        }
        if(slopehb > 0 && horizontalbottom[i]>170 && foundhb == 0)  //Bottom Earth on Bottom of Picture
        {
            foundhb = 1;
            foundhbleft = 2;
            earthdata[6] = i;
            earthdata[7] = 1;
        }
        if(slopehb < 0 && horizontalbottom[i]>170 && foundhbleft <2)   //Bottom Earth on Top of Picture
        {
            foundhbleft = 1;
            foundhb = 1;
            earthdata[6] = i;
            earthdata[7] = -1;
        }

    }

     for(j=0;j<8;j++)
    {
      //  printf(" %d \n", earthdata[j] );

    }

return;
}
