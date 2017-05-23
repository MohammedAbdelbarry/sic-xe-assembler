/**
 * @file numutil.cpp
 * The file containing the numerical utilities namespace implementation.
 */
#include <sstream>
#include <bitset>
#include <algorithm>
#include <regex>
#include "../headers/strutil.h"
#include "../headers/numutil.h"

const int HEX_BASE = 16;
const int BIN_BASE = 2;
const int INTEGER_SIZE_IN_BITS = 32;

std::string numutil::Hexadecimal::toBin(std::string number) {
    std::stringstream stringStream;
    stringStream << std::hex << number;
    unsigned int num;
    stringStream >> num;
    std::bitset<INTEGER_SIZE_IN_BITS> bSet(num);
    return bSet.to_string();
}

int numutil::Hexadecimal::toDec(std::string number) {
    return (int)std::strtol(number.c_str(), nullptr, HEX_BASE);
}

std::string numutil::Decimal::toBin(int number) {
    std::string hexadecimalNumber = numutil::Decimal::toHex(number);
    return numutil::Hexadecimal::toBin(hexadecimalNumber);
}

std::string numutil::Decimal::toHex(int number) {
    std::stringstream stringStream;
    stringStream << std::hex << number;
    std::string hexadecimalNumber = stringStream.str();
    std::transform(hexadecimalNumber.begin(), hexadecimalNumber.end(),
                   hexadecimalNumber.begin(), toupper);
    return hexadecimalNumber;
}

std::string numutil::Decimal::toString(int number) {
    std::ostringstream stringStream;
    stringStream << number;
    return stringStream.str();
}

std::string numutil::Binary::toHex(std::string number) {
    int hexadecimalNumber = numutil::Binary::toDec(number);
    return numutil::Decimal::toHex(hexadecimalNumber);
}

int numutil::Binary::toDec(std::string number) {
    return (int)std::strtol(number.c_str(), nullptr, BIN_BASE);
}

std::string numutil::Hexadecimal::parseHexadecimalLiteral(std::string hexLiteral) {
    return hexLiteral.substr(2, hexLiteral.length() - 3);
}

bool numutil::Hexadecimal::isHexLiteral(std::string hexLiteral) {
    static const std::regex hexLiteralRegex("^[Xx]'[0-9A-Fa-f]+'$");
    return strutil::matches(hexLiteral, hexLiteralRegex);
}

//TODO search for an alternative using stringStream lib
std::string numutil::Hexadecimal::toString(std::string hexString){
    std::string characterString;
    if (hexString.size() & 1) {
        throw std::invalid_argument("Hexadecimal string of odd length");
    }
    int decimalValue;
    std::string character;
    for (int i = 0 ; i < hexString.size() ; i+=2) {
        decimalValue = numutil::Hexadecimal::toDec(hexString.substr(i,2));
        characterString.push_back(char(decimalValue));
    }
    return characterString;
}
