#include "list_select.h"

using namespace std;


void apply_surface( int x, int y, SDL_Surface* source, SDL_Surface* destination )
{        
    //Temporary rectangle to hold the offsets
    SDL_Rect offset;
        
    //Get the offsets
    offset.x = x;
    offset.y = y;
    
    //Blit the surface
    SDL_BlitSurface( source, NULL, destination, &offset );
}


ListSelect::ListSelect(stringvec& items_in, int pageSize_in):items(items_in), pageSize(pageSize_in) {
  items = items_in;
  pageSize = pageSize_in;
  selected_item = items.begin();
  first_onscreen = items.begin();
  if (items.size() > pageSize) {
    last_onscreen = items.begin() + pageSize;
  } else {
    last_onscreen = items.end();
  }
  TTF_Init();
}

void ListSelect::Draw(SDL_Surface* screen) {
  TTF_Font* font = TTF_OpenFont("/usr/share/bunnymenu/mainfont.ttf", FONT_SIZE);
  SDL_Color textColor = {255,255,255};
  SDL_Color selectedColor = {255, 0, 255};
  SDL_Surface* message = NULL;  
  stringvec::iterator it = items.begin();
  int item = 0;
  for(it = first_onscreen; it !=last_onscreen; it++) 
  {
      if(it == selected_item) {
        message = TTF_RenderText_Solid(font, (*it).c_str(), selectedColor);
      } else {
        message = TTF_RenderText_Solid(font, (*it).c_str(), textColor);
      }
      apply_surface(LEFT_MARGIN, item*(FONT_SIZE+PIXEL_SPACING)+TOP_MARGIN, message, screen);
      SDL_FreeSurface(message);
      item++;
    }
  TTF_CloseFont(font);
  }

std::string ListSelect::ChooseItem(SDL_Surface* screen, Background* backgnd) {
  int run = 1;
  SDL_Event event;
  while (run) {
    backgnd->Draw();
    Draw(screen);
    SDL_Flip(screen);
    while (SDL_WaitEvent(&event) && run) {
      if (event.type == SDL_QUIT) {
        run = 0;
	return "QUIT";
      } else if (event.type == SDL_KEYDOWN) {
        switch (event.key.keysym.sym) {
        case SDLK_UP:
          ScrollPrevious();
          break;
	case SDLK_l:
	case SDLK_PAGEUP:
	  ScrollPreviousMulti(pageSize);
	  break;
        case SDLK_DOWN:
          ScrollNext();
          break;
	case SDLK_PAGEDOWN:
	case SDLK_r:
	  ScrollNextMulti(pageSize);
	  break;
        case SDLK_RETURN:
	case SDLK_b:
	case SDLK_u:
          run = 0;
          break;
	case SDLK_a:
	case SDLK_d:
	  run = 0;
	  return "BACK";
        default:
          break;
	}
      backgnd->Draw();
      Draw(screen);
      SDL_Flip(screen);
      }
    }
  }
  return GetCurrent();
}

void ListSelect::ScrollNext() {
  if (std::next(selected_item) != items.end()) {
    selected_item++;
}
  if (selected_item >= last_onscreen) {
    first_onscreen++;
    last_onscreen++;
  }


}

void ListSelect::ScrollPrevious() {
 if (selected_item != items.begin()) {
  if (selected_item <= first_onscreen) {
    first_onscreen--;
    last_onscreen--;
  }
  selected_item--;
 }
}

void ListSelect::ScrollNextMulti(int lines) {
  for(int i=0; i < lines; i++) {
    ScrollNext();
  }
}

void ListSelect::ScrollPreviousMulti(int lines) {
  for(int i=0; i < lines; i++) {
    ScrollPrevious();
  }
}



std::string ListSelect::GetCurrent() {
  return *selected_item;
}


int main2() {
  Background background = Background("/usr/share/bunnymenu/background.jpg", 320, 240, 32);
  TTF_Init();
  stringvec list;
  for(int i = 0; i < 8; i++) {
    list.push_back("foo");
    list.push_back("bah");
    list.push_back("bar");
  }
  ListSelect sel = ListSelect(list, 10);
  std::string test = sel.ChooseItem(background.GetScreen(), &background);
  cout << "Test: " << test << endl;
  SDL_Quit();
}
