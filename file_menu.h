#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <sys/types.h>
#include <dirent.h>
#include "list_select.h"
#include "background.h"

using namespace std;

typedef std::vector<std::string> stringvec;
typedef std::map<std::string, std::string> stringmap;

class FileMenu {
  std::string current_dir;
  std::string top_dir;
public:
  FileMenu(std::string init_dir);
  std::string ChooseItem(Background &background);
};

