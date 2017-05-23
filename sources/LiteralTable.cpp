#include <string>
#include <map>
#include <vector>
#include <regex>
#include "../headers/LiteralInfo.h"
#include "../headers/LiteralTable.h"
#include "../headers/strutil.h"

void LiteralTable::push(std::string literal, LiteralInfo literalInfo) {
    LiteralTable::litTab[strutil::toUpper(literal)] = literalInfo;
}

bool LiteralTable::contains(std::string literal) {
    return LiteralTable::litTab.find(strutil::toUpper(literal)) != LiteralTable::litTab.end();
}

LiteralInfo& LiteralTable::getInfo(std::string literal) {
    return LiteralTable::litTab[strutil::toUpper(literal)];
}

std::map<std::string, LiteralInfo>& LiteralTable::getMap() {
    return LiteralTable::litTab;
}
