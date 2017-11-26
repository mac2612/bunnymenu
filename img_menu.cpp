#include "img_menu.h"
#include <unistd.h>

ImgMenu::ImgMenu(stringmap imgList_in, Background* backgnd_in) {
  imgList = imgList_in;
  active_img = imgList.begin();
  backgnd = backgnd_in;
}

void ImgMenu::ScrollNext() {
  if (std::next(active_img) == imgList.end()) {
    active_img = imgList.begin();
  } else {
    ++active_img;
  }
}

void ImgMenu::ScrollPrevious() {
  if (active_img == imgList.begin()) {
    active_img = std::prev(imgList.end());
  } else {
    --active_img;
  }
}

std::string ImgMenu::GetCurrent() { return active_img->first; }

void ImgMenu::Draw(SDL_Surface *screen) {
  SDL_Surface *img = NULL;
  img = IMG_Load(active_img->second.c_str());
  SDL_Rect offset;
  offset.x = (screen->w / 2) - (img->w / 2);
  offset.y = (screen->h / 2) - (img->h / 2);
  SDL_BlitSurface(img, NULL, screen, &offset);
  SDL_Flip(screen);
  SDL_FreeSurface(img);
}

std::string ImgMenu::ChooseItem() {
  SDL_Surface *screen = backgnd->GetScreen();
  int run = 1;
  SDL_Event event;
  Uint8 *state = SDL_GetKeyState(NULL);

  while (run) {
    backgnd->Draw();
    Draw(screen);
    while (SDL_WaitEvent(&event) >= 0 && run) {
      //If the user has Xed out the window
      if( event.type == SDL_QUIT ) {
        //Quit the program
        run = false;
	return "QUIT";
      }
 
      if (event.type == SDL_KEYDOWN) {
        switch (event.key.keysym.sym) {
        case SDLK_LEFT:
          ScrollPrevious();
          break;
        case SDLK_RIGHT:
          ScrollNext();
          break;
        case SDLK_RETURN:
        case SDLK_b:
	case SDLK_u:
          run = 0;
          break;
        default:
          break;
        }
        backgnd->Draw();
	Draw(screen);

    }
}
    //if(state[SDLK_LEFT]) {
    //  ScrollPrevious();
    //}
    //if(state[SDLK_RIGHT]) {
    //  ScrollNext();
    //}
    //cout << "state:" << state << endl;
    //state = SDL_GetKeyState(NULL);
    //usleep(200000);
    }
  return GetCurrent();
}

int not_main(int argc, char *args[]) {
  Background background = Background("background.jpg", 320, 240, 32);
  stringmap list;
  list.insert(std::make_pair("NES", "nes.png"));
  list.insert(std::make_pair("SNES", "snes.png"));

  ImgMenu menu = ImgMenu(list, &background);
  std::cout << "The user selected: " << menu.ChooseItem() << endl;
  SDL_Quit();

  return 0;
}

