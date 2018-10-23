#!/bin/sh
SCREEN_WIDTH=320
SCREEN_HEIGHT=240

while `true`
do
  export SDL_NOMOUSE=1
  bunnymenu -w $SCREEN_WIDTH -h $SCREEN_HEIGHT 2> /root/bunny.log
  echo "Restarting program..."
done

