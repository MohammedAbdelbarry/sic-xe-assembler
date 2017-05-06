//
// Created by salem.harby on 05/04/2017.
//

#include <algorithm>
#include <regex>
#include <iomanip>
#include <iostream>
#include "../headers/strutil.h"
#include "../headers/InstructionInfo.h"
#include "../headers/OperationTable.h"


std::string concatenateLine(std::sregex_token_iterator &iterator, std::sregex_token_iterator &end) {
    std::stringstream stringStream;
    while (iterator != end) {
        stringStream << " " << *iterator;
        iterator++;
    }
    return stringStream.str();
}

std::vector<std::string> strutil::split(std::string str, std::regex &regex, int splitsNumber) {
    int splittingCounter = 0;
    std::vector<std::string> ret;
    if (strutil::beginWith(str, ".")) {
        ret.push_back(str);
        return ret;
    }
    std::sregex_token_iterator iter(str.begin(), str.end(), regex, -1);
    std::sregex_token_iterator end;
    while (iter != end) {
        std::string cur = *iter;
        ret.push_back(cur);
        iter++;
        splittingCounter++;
        if(splittingCounter == splitsNumber
                || (OperationTable::getInstance()->contains(cur)
                    && OperationTable::getInstance()->getInfo(cur).supportedFormats[0] == InstructionFormat::ONE)) {
            ret.push_back(concatenateLine(iter, end));
            break;
        }
    }
    return ret;
}

bool strutil::matches(std::string str, std::regex regex) {
    return std::regex_match(str, regex);
}

bool strutil::endsWith(std::string const &value, std::string const &ending) {
    if (ending.size() > value.size())
        return false;
    return std::equal(ending.rbegin(), ending.rend(), value.rbegin());
}

bool ::strutil::beginWith(std::string const &value, std::string const &beginning) {
    if (beginning.size() > value.size())
        return false;
    return std::equal(beginning.begin(), beginning.end(), value.begin());
}

std::string strutil::parseCharLiteral(std::string charLiteral) {
    return charLiteral.substr(2, charLiteral.length() - 3);
}
void strutil::addHex(std::ostringstream& stringStream, int decimalNumber, int numChars) {
    stringStream << std::hex << std::setfill('0') << std::setw(numChars)
                 << std::right << std::uppercase << decimalNumber;
}
bool strutil::isCharLiteral(std::string charLiteral) {
    static const std::regex charLiteralRegex("^[Cc]'[^']+?'$");
    return matches(charLiteral, charLiteralRegex);
}

std::string strutil::toUpper(std::string str) {
    std::transform(str.begin(), str.end(), str.begin(), toupper);
    return str;
}


