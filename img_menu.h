#include <iostream>
#include <iterator>
#include <map>
#include <string>
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "background.h"
using namespace std;

typedef std::map<std::string, std::string> stringmap;

class ImgMenu {
  stringmap imgList;
  stringmap::iterator active_img;
  Background* backgnd = NULL;

 public:
  ImgMenu(stringmap imgList_in, Background* backgnd_in);
  void ScrollPrevious();
  void ScrollNext();
  std::string GetCurrent();
  void Draw(SDL_Surface* screen);
  std::string ChooseItem();
};
