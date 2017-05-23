#include <string>
#include <iostream>
#include <map>
#include <regex>
#include "../headers/enums.h"
#include "../headers/Error.h"
#include "../headers/DirectiveInfo.h"
#include "../headers/DirectiveTable.h"
#include "../headers/numutil.h"
#include "../headers/Assembler.h"
#include "../headers/strutil.h"

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cout << "Invalid Number of Parameters" << std::endl;
        return 1;
    }
    std::string fileName(argv[1]);
    try {
        Assembler::getInstance()->execute(fileName, std::map<std::string, std::string>());
    } catch (std::invalid_argument ex) {
        std::cout << ex.what();
    }
}