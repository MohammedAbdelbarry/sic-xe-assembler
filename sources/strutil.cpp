//
// Created by salem.harby on 05/04/2017.
//

#include <algorithm>
#include <regex>
#include <iomanip>
#include "../headers/strutil.h"

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
    std::sregex_token_iterator iter(str.begin(), str.end(), regex, -1);
    std::sregex_token_iterator end;
    while (iter != end) {
        if(splittingCounter == splitsNumber) {
            ret.push_back(concatenateLine(iter, end));
            break;
        }
        std::string cur = *iter;
        ret.push_back(cur);
        iter++;
        splittingCounter++;
    }
    return ret;
}

bool strutil::matches(std::string str, std::regex regex) {
    return std::regex_match(str, regex);
}

void strutil::addHex(std::ostringstream& stringStream, int decimalNumber, int numChars) {
    stringStream << std::hex << std::setfill('0') << std::setw(numChars) << std::right << std::uppercase << decimalNumber;
}
