/**
 * @file LiteralTable.cpp
 * The file containing the literal table class implementation.
 */
#include "../headers/LiteralInfo.h"
#include "../headers/LiteralTable.h"
#include "../headers/strutil.h"

void LiteralTable::push(std::string literal, LiteralInfo literalInfo) {
    LiteralTable::keySet.push_back(literal);
    LiteralTable::litTab.insert(std::make_pair(literal, literalInfo));
}

bool LiteralTable::contains(std::string literal) {
    return LiteralTable::litTab.find(strutil::toUpper(literal)) != LiteralTable::litTab.end();
}

LiteralInfo& LiteralTable::getInfo(std::string literal) {
    return LiteralTable::litTab[strutil::toUpper(literal)];
}

std::vector<std::string>& LiteralTable::getKeySet() {
    return LiteralTable::keySet;
}
