#include <iostream>
#include <string>
#include <vector>
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "SDL/SDL_ttf.h"
#include "background.h"

#define FONT_SIZE 12
#define PIXEL_SPACING 3
#define LEFT_MARGIN 15
#define TOP_MARGIN 5
#define BOTTOM_MARGIN 5

typedef std::vector<std::string> stringvec;

class ListSelect {
  stringvec& items;
  stringvec::iterator selected_item;
  stringvec::iterator first_onscreen;
  stringvec::iterator last_onscreen;
  int pageSize;
  void Draw(SDL_Surface* screen);

 public:
  ListSelect(stringvec& items_in, int pageSize_in);
  std::string ChooseItem(SDL_Surface* screen, Background* background);
  void ScrollPrevious();
  void ScrollPreviousMulti(int lines);
  void ScrollNext();
  void ScrollNextMulti(int lines);
  std::string GetCurrent();
};
