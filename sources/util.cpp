//
// Created by Mohamed A.Tolba on 5/4/2017.
//

#include <sstream>
#include <bitset>
#include <algorithm>
#include "../headers/util.h"


const int HEX_BASE = 16;
const int BIN_BASE = 2;
const int INTEGER_SIZE_IN_BITS = 32;

std::string util::Hexadecimal::toBin(std::string number) {
    std::stringstream stringStream;
    stringStream << std::hex << number;
    unsigned int num;
    stringStream >> num;
    std::bitset<INTEGER_SIZE_IN_BITS> bSet(num);
    return bSet.to_string();
}

int util::Hexadecimal::toDec(std::string number) {
    return (int)std::strtol(number.c_str(), nullptr, HEX_BASE);
}

std::string util::Decimal::toBin(int number) {
    std::string hexadecimalNumber = util::Decimal::toHex(number);
    return util::Hexadecimal::toBin(hexadecimalNumber);
}

std::string util::Decimal::toHex(int number) {
    std::stringstream stringStream;
    stringStream << std::hex << number;
    std::string hexadecimalNumber = stringStream.str();
    std::transform(hexadecimalNumber.begin(), hexadecimalNumber.end(),
                   hexadecimalNumber.begin(), toupper);
    return hexadecimalNumber;
}

std::string util::Decimal::toString(int number) {
    std::ostringstream stringStream;
    stringStream << number;
    return stringStream.str();
}

std::string util::Binary::toHex(std::string number) {
    int hexadecimalNumber = util::Binary::toDec(number);
    return util::Decimal::toHex(hexadecimalNumber);
}

int util::Binary::toDec(std::string number) {
    return (int)std::strtol(number.c_str(), nullptr, BIN_BASE);
}

std::string util::Hexadecimal::parseHexadecimalLiteral(std::string hexLiteral) {
    return hexLiteral.substr(2, hexLiteral.length() - 3);
}