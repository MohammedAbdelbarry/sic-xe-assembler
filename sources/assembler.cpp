#include "assembler.h"
#include <fstream>

void assembler::executePass1(std::string fileName, std::map<std::string, std::string> options) {
    std::ifstream file(fileName);
    std::string line;
    while (std::getline(file, line)) {

    }
}

void assembler::executePass2(std::string intermediateFileName) {

}