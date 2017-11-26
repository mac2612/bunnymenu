#include "background.h"
#include "img_menu.h"
#include "input_parser.h"
#include "file_menu.h"
#include <stdlib.h>
#include <unistd.h>
#include <algorithm>

const int DEFAULT_WIDTH = 320;
const int DEFAULT_HEIGHT = 240;
const int DEFAULT_BPP = 32;


int exec_from_filename(std::string cmd, std::string filename) {
  SDL_Quit();
  std::string full = "/usr/bin/" + cmd;
  std::string command = "startsnes.sh";
  cout << "Executing: command: " << full << "File: " << filename << endl;
  return execlp(full.c_str(), cmd.c_str(), filename.c_str(), NULL);
}


int main(int argc, char **argv) {

  InputParser input(argc, argv);
  int height = input.parseIntOption("-h", DEFAULT_HEIGHT);
  int width = input.parseIntOption("-w", DEFAULT_WIDTH);
  int bpp = input.parseIntOption("-d", DEFAULT_BPP);

  while(1) {
  Background background = Background("/usr/share/bunnymenu/background.jpg", width, height, bpp);
  stringmap list;
  list.insert(std::make_pair("NES", "/usr/share/bunnymenu/nes.png"));
  list.insert(std::make_pair("SNES", "/usr/share/bunnymenu/snes.png"));
  ImgMenu imgmenu = ImgMenu(list, &background);
  std::string selection = imgmenu.ChooseItem();
  std::string cmd = "";
  std::string path = "~";
  if(selection == "NES"){
    path = "/roms/nes/";
    cmd = "startnes.sh";
  } else if(selection == "SNES"){
    path = "/roms/snes/";
    cmd = "startsnes.sh";
  } else if(selection == "QUIT"){
    return 0;
  }
  FileMenu filemenu = FileMenu(path);
  std::string test = filemenu.ChooseItem(background);
  if(test == "QUIT") {
    return 0;
  }
  if(test != "BACK") {
    cout << "You chose: " << test << ". Executing..." <<  endl;
    cout << "Result:" << exec_from_filename(cmd, path + test) << endl;
    }
  }
}
