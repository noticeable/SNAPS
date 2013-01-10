#define heightbit1 0x02
#define heightbit2 0x40
#define widthbit1 0x04
#define widthbit2 0x00
#define Heights  576
#define Widths 1024
#define GreenFilter 0.1
#define RedFilter 0.25
#define BlueFilter 0.5
#define whitefilterblue 170
#define whitefilterred 170
#define whitefiltergreen 170
#define whitefilterthreshold 0.04
#define circledetectmatrixsize 16
#define h264buffersize 3000000
#define file_name "SDCard/Video/video.mov"


#ifndef MAIN_H_
#define MAIN_H_
typedef struct {
    unsigned int position;                       /* Position of Frame in Video      */
    unsigned int width,height;                   /* Width and height of Frame */
    unsigned char framebits[Heights][Widths*3];  /* RGB Matrix    */
} FRAMECHAR;


#endif /* MAIN_H_ */

extern int main(void);
