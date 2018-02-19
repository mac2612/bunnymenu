#include <string>
#include "SDL/SDL_image.h"

#ifndef BACKGROUND_H
#define BACKGROUND_H
class Background {
  std::string imgName;
  SDL_Surface *screen;
  SDL_Surface *background;

 public:
  Background(std::string imgName_in, int width, int height, int bpp);
  void Draw();
  SDL_Surface *GetScreen();
};
#endif /* BACKGROUND_H */
