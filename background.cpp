#include "SDL/SDL_image.h"
#include <string>
#include "background.h"

using namespace std;


Background::Background(std::string imgName_in, int width, int height, int bpp) {
  imgName = imgName_in;
  SDL_Init(SDL_INIT_EVERYTHING);
  screen = SDL_SetVideoMode(width, height, bpp, SDL_SWSURFACE);
  SDL_ShowCursor(SDL_DISABLE);
  background = IMG_Load(imgName.c_str());
}

void Background::Draw() {
  // Every background draw should start with a blank screen.
  SDL_FillRect(screen, NULL, 0x000000);
  SDL_BlitSurface(background, NULL, screen, NULL);
}

SDL_Surface* Background::GetScreen() {
  return screen;
}
