all:
	cc -o demuxer demuxer.c -lavformat -lavcodec -lz 
	cc -arch i386 -m32 -o decoder decoder.c -lhollowcore-h264 -L../hollowcore-h264/
