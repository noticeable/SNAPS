#!/bin/sh

ffmpeg -i $1 -vcodec copy -bsf h264_mp4toannexb -an -f rawvideo out.h264