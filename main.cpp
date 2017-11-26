#include "background.h"
#include "img_menu.h"
#include "file_menu.h"
#include <stdlib.h>
#include <unistd.h>

int exec_from_filename(std::string cmd, std::string filename) {
  SDL_Quit();
  std::string full = "/usr/bin/" + cmd;
  std::string command = "startsnes.sh";
  cout << "Executing: command: " << full << "File: " << filename << endl;
  return execlp(full.c_str(), cmd.c_str(), filename.c_str(), NULL);
}      

int main() {
  while(1) {
  Background background = Background("/usr/share/bunnymenu/background.jpg");
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
    //cout << cmd << " " << path << test;
    //return 0;
    }
  }
}
