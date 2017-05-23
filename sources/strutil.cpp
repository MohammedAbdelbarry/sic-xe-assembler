/**
 * @file strutil.cpp
 * The file containing the string utilities namespace implementation.
 */
#include <algorithm>
#include <regex>
#include <iomanip>
#include <iostream>
#include "../headers/strutil.h"
#include "../headers/InstructionInfo.h"
#include "../headers/OperationTable.h"

const std::string HEX_BASE_NUMBERS = "0123456789ABCDEF";
const int HEX_BASE = 16;
const int NIBBLE = 4;
const std::regex leftTrimReg("^\\s+");
const std::regex rightTrimReg("\\s+$");

std::string concatenateLine(std::sregex_token_iterator &iterator, std::sregex_token_iterator &end) {
    std::stringstream stringStream;
    //TODO check for this fishy conditioning in the if-statement in the while loop;
    /* it can be substituted with adding white spaces for every append
     * operation in the stringStream then trimming the extra one white space at the end.
     */
    while (iterator != end) {
        stringStream << *iterator;
        iterator++;
        if (iterator != end) {
            stringStream << " ";
        }
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
        if(splittingCounter == splitsNumber) {
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

//TODO search for an alternative using stringStream lib
std::string strutil::toHex(std::string str){
    std::string hexadecimalString;
    int characterDecimalValue;
    for (int i=0 ; i < str.size() ; i++) {
        characterDecimalValue = str[i];
        hexadecimalString.push_back(HEX_BASE_NUMBERS[characterDecimalValue >> NIBBLE]);
        //alternative for taking the modulo due to its performance issues.
        hexadecimalString.push_back(HEX_BASE_NUMBERS[characterDecimalValue & (HEX_BASE - 1)]);
    }
    return hexadecimalString;
}

std::string fileutil::removeExtension(std::string str) {
    int lastIndex = str.find_last_of(".");
    if (lastIndex != std::string::npos) {
        return str.substr(0, lastIndex);
    }
    return str;
}


std::string strutil::trim(std::string str) {
    const std::string none = "";
    std::string trimmed = std::regex_replace(str, leftTrimReg, none);
    return std::regex_replace(trimmed, rightTrimReg, none);
}