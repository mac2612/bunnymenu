#include <algorithm>
#include <stdlib.h>
#include <unistd.h>
#include <string>
#include <vector>

using namespace std;

class InputParser{
  public:
    InputParser (int &argc, char **argv);
    const std::string getCmdOption(const std::string &option);
    bool cmdOptionExists(const std::string &option);
    const int parseIntOption(const std::string &option, const int default_val);
  private:
    std::vector <std::string> tokens;
};
