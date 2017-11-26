#include "file_menu.h"
#include <algorithm>

void read_directory(const std::string& name, stringvec& v)
{
    DIR* dirp = opendir(name.c_str());
    struct dirent * dp;
    while ((dp = readdir(dirp)) != NULL) {
        v.push_back(dp->d_name);
    }
    closedir(dirp);
}


FileMenu::FileMenu(std::string init_dir) {
  current_dir = init_dir;
  top_dir = init_dir;
}

std::string FileMenu::ChooseItem(Background &background) {
  stringvec files;
  read_directory(current_dir, files);
  sort(files.begin(), files.end());
  files.erase(std::remove(files.begin(), files.end(), "."), files.end());
  files.erase(std::remove(files.begin(), files.end(), ".."), files.end());
  ListSelect selector = ListSelect(files, (background.GetScreen()->h / 16));
  std::string test = selector.ChooseItem(background.GetScreen(), &background);
  //cout << "Read directory: " << files.begin() << "end: " << files.end() << endl;
  return test;
}


int not_main() {
  FileMenu menu = FileMenu("/home/forrie");
  //std::string test = menu.ChooseItem();
  //cout << "You chose: " << test << endl;
  return 0;
}
