#include <string>
#include <iostream>
#include "../headers/Assembler.h"
#include "../headers/DirectiveTable.h"

int main() {
    int locCtr = 1;
    DirectiveTable::getInstance()->getInfo("WORD").execute.operator()(locCtr, Line("a", "b", "c"));
    std::cout << locCtr;
}