#include <string>
#include <iostream>
#include <map>
#include <regex>
#include "../headers/enums.h"
#include "../headers/Error.h"
#include "../headers/DirectiveInfo.h"
#include "../headers/DirectiveTable.h"
#include "../headers/util.h"
#include "../headers/Assembler.h"
#include "../headers/strutil.h"

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cout << "Invalid Number of Parameters" << std::endl;
        return 1;
    }
    std::string fileName(argv[1]);
//    int locCtr = 1;
//    DirectiveTable::getInstance()->getInfo("WORD").execute.operator()(locCtr, Line("a", "b", "c"));
//    std::cout << locCtr;
//    //--------------------------------
//    std::cout << numutil::Hexadecimal::toBin("A1") << std::endl;
//    //00000000000000000000000010100001
//    std::cout << numutil::Hexadecimal::toDec("A1") << std::endl;
//    //161
//    std::cout << numutil::Decimal::toBin(-45088) << std::endl;
//    //11111111111111110100111111100000
//    std::cout << numutil::Decimal::toHex(-45088) << std::endl;
//    //FFFF4FE0
//    std::cout << numutil::Decimal::toString(45088) << std::endl;
//    //"45088"
//    std::cout << numutil::Binary::toHex("00000000001111110000") << std::endl;
//    //3fo
//    std::cout << numutil::Binary::toDec("00000000001111110000") << std::endl;
//    //1008
    try {
        Assembler::getInstance()->execute(fileName, std::map<std::string, std::string>());
    } catch (std::invalid_argument ex) {
        std::cout << ex.what();
    }
}