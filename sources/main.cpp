#include <string>
#include <iostream>
#include "../headers/Assembler.h"
#include "../headers/DirectiveTable.h"
#include "../headers/util.h"


int main() {
    int locCtr = 1;
    DirectiveTable::getInstance()->getInfo("WORD").execute.operator()(locCtr, Line("a", "b", "c"));
    std::cout << locCtr;



    std::cout << util::Hexadecimal::toBin("A1") << std::endl;
    //00000000000000000000000010100001
    std::cout << util::Hexadecimal::toDec("A1") << std::endl;
    //161
    std::cout << util::Decimal::toBin(-45088) << std::endl;
    //11111111111111110100111111100000
    std::cout << util::Decimal::toHex(-45088) << std::endl;
    //FFFF4FE0
    std::cout << util::Decimal::toString(45088) << std::endl;
    //"45088"
    std::cout << util::Binary::toHex("00000000001111110000") << std::endl;
    //3fo
    std::cout << util::Binary::toDec("00000000001111110000") << std::endl;
    //1008

}