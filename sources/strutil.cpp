//
// Created by salem.harby on 05/04/2017.
//

#include <algorithm>
#include <regex>
#include <iomanip>
#include "../headers/strutil.h"

std::vector<std::string> strutil::split(std::string str, std::regex regex) {
    std::vector<std::string> ret;
    std::transform(str.begin(), str.end(), str.begin(), toupper);
    std::sregex_token_iterator iter(str.begin(), str.end(), regex, -1);
    std::sregex_token_iterator end;
    while (iter != end) {
        std::string cur = *iter;
        ret.push_back(cur);
    }
    return ret;
}

bool strutil::matches(std::string str, std::regex regex) {
    return std::regex_match(str, regex);
}

void strutil::addHex(std::ostringstream& stringStream, int decimalNumber, int numChars) {
    stringStream << std::hex << std::setfill('0') << std::setw(numChars) << std::right << std::uppercase << decimalNumber;
}
