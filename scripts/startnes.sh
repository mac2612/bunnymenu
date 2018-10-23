#!/bin/sh
RETROARCH_CFG=/configs/retroarch.cfg.leapstergs

if dmesg | grep "valencia" > /dev/null
then
  RETROARCH_CFG=/configs/retroarch.cfg.leappad2
fi

SDL_NOMOUSE=1 retroarch -s /roms/saves -S /roms/saves -v -c $RETROARCH_CFG -L /usr/lib/libretro/fceumm_libretro.so "$*"
