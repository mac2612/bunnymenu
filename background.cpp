#include "SDL/SDL_image.h"
#include <string>
#include "background.h"

//The attributes of the screen
#if defined(DEVICE_LEAPGS)
const int SCREEN_WIDTH = 320;
const int SCREEN_HEIGHT = 240;
#else
const int SCREEN_WIDTH = 480;
const int SCREEN_HEIGHT = 272;
#endif
const int SCREEN_BPP = 32;

using namespace std;


Background::Background(std::string imgName_in) {
  imgName = imgName_in;
  SDL_Init(SDL_INIT_EVERYTHING);
  screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_SWSURFACE);
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
