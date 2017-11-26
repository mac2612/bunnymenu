#include "input_parser.h"


// Shamelessly borrowed from https://stackoverflow.com/questions/865668
	    InputParser::InputParser (int &argc, char **argv){
            for (int i=1; i < argc; ++i)
                this->tokens.push_back(std::string(argv[i]));
        }
        /// @author iain
        const std::string InputParser::getCmdOption(const std::string &option) {
            std::vector<std::string>::const_iterator itr;
            itr =  std::find(this->tokens.begin(), this->tokens.end(), option);
            if (itr != this->tokens.end() && ++itr != this->tokens.end()){
                return *itr;
            }
            static const std::string empty_string("");
            return empty_string;
        }
        /// @author iain
        bool InputParser::cmdOptionExists(const std::string &option) {
            return std::find(this->tokens.begin(), this->tokens.end(), option)
                   != this->tokens.end();
        }
	const int InputParser::parseIntOption(const std::string &option, const int default_val) {
	    int ret = default_val;
	    const std::string buf = this->getCmdOption(option);
	    if (!buf.empty()) {
              ret = strtol(buf.c_str(), NULL, 0);
	    }
	    return ret;
	}

