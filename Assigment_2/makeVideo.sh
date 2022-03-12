#!/bin/bash
#convert  pgm to pgn image
for i in *.pgm;
  do name=`echo "$i" | cut -d'.' -f1`
  echo "$name"
  ffmpeg -i "$i" "${name}.png"
done
#make video
ffmpeg -framerate 15 -pattern_type  glob -i "*.png" video.mp4
