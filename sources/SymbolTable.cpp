//
// Created by salem.harby on 05/01/2017.
//

#include <string>
#include <map>
#include <regex>
#include <vector>
#include "../headers/strutil.h"
#include "../headers/SymbolTable.h"

void SymbolTable::push(std::string label, int address) {
    SymbolTable::symTab[strutil::toUpper(label)] = address;
}

bool SymbolTable::contains(std::string label) {
    return SymbolTable::symTab.find(strutil::toUpper(label)) != SymbolTable::symTab.end();
}

int SymbolTable::getAddress(std::string label) {
    return SymbolTable::symTab[strutil::toUpper(label)];
}