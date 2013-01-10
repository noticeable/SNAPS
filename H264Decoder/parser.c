#include "../main.h"
#include <stdlib.h>
#include <stdio.h>
#include "bs.h"



int readchunk(int startposition, unsigned char *h264buffer)
{
    unsigned char q;
    int j;
    int nal_start;
    int nal_end;
    nal_start = 0;
    nal_end = 0;
    FILE *file;

	file = fopen("SDCard/Video/video.mov", "rb");
	if (!file)
	{
		fprintf(stderr, "Unable to open file %s", file_name);
		return;
	}

	fseek(file, startposition, SEEK_SET);
	fread(h264buffer,1, h264buffersize, file);
   j =  find_nal_units(h264buffer,&nal_start,&nal_end);
    printf("NAL Start Position: %d  \nNAL End Position: %d \nNAL Length: %d \n", nal_start,nal_end, j);
    find_nal_unit_type(h264buffer,&nal_start);
    return(0);

}

void find_nal_unit_type(unsigned char *buf, int *nal_start)
{
    int j;
    bs_t* b = bs_new(buf, h264buffersize);
    j = bs_read_u(b,5);
    printf("%d \n \n ",j);
    return;
}

int find_nal_units(unsigned char* buf, int* nal_start, int* nal_end)
{
    int i;
    // find start
    *nal_start = 0;
    *nal_end = 0;
    int size;
    size = h264buffersize;

    i = 0;
    while (   //( next_bits( 24 ) != 0x000001 && next_bits( 32 ) != 0x00000001 )
        (buf[i] != 0 || buf[i+1] != 0 || buf[i+2] != 0x01) &&
        (buf[i] != 0 || buf[i+1] != 0 || buf[i+2] != 0 || buf[i+3] != 0x01)
        )
    {
        i++; // skip leading zero
        if (i+4 >= size) { return 0; } // did not find nal start
    }

    if  (buf[i] != 0 || buf[i+1] != 0 || buf[i+2] != 0x01) // ( next_bits( 24 ) != 0x000001 )
    {
        i++;
    }

    if  (buf[i] != 0 || buf[i+1] != 0 || buf[i+2] != 0x01) { /* error, should never happen */ return 0; }
    i+= 3;
    *nal_start = i;

    while (   //( next_bits( 24 ) != 0x000000 && next_bits( 24 ) != 0x000001 )
        (buf[i] != 0 || buf[i+1] != 0 || buf[i+2] != 0) &&
        (buf[i] != 0 || buf[i+1] != 0 || buf[i+2] != 0x01)
        )
    {
        i++;
        // FIXME the next line fails when reading a nal that ends exactly at the end of the data
        if (i+3 >= size) { *nal_end = size; return -1; } // did not find nal end, stream ended first
    }

    *nal_end = i;
    return (*nal_end - *nal_start);
}
