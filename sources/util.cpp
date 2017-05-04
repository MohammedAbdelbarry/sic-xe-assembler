//
// Created by Mohamed A.Tolba on 5/4/2017.
//

#include "../headers/util.h"
#include <sstream>
#include <bitset>
#include <cstdlib>
#include <algorithm>


const int HEX_BASE = 16;
const int BIN_BASE = 2;
const int INTEGER_SIZE_IN_BITS = 32;

std::string util::Hexadecimal::toBin(std::string number) {
    std::stringstream stream;
    stream << std::hex << number;
    unsigned int num;
    stream >> num;
    std::bitset<INTEGER_SIZE_IN_BITS> bSet(num);
    return bSet.to_string();
}

int util::Hexadecimal::toDec(std::string number) {
    return (int)std::strtol(number.c_str(), nullptr, HEX_BASE);
}

std::string util::Decimal::toBin(int number) {
    std::string num = util::Decimal::toHex(number);
    return util::Hexadecimal::toBin(num);
}

std::string util::Decimal::toHex(int number) {
    std::stringstream stream;
    stream << std::hex << number;
    std::string result = stream.str();
    std::transform(result.begin(), result.end(), result.begin(), toupper);
    return result;
}

std::string util::Decimal::toString(int number) {
    std::ostringstream stream;
    stream << number;
    return stream.str();
}

std::string util::Binary::toHex(std::string number) {
    int num = util::Binary::toDec(number);
    return util::Decimal::toHex(num);
}

int util::Binary::toDec(std::string number) {
    return (int)std::strtol(number.c_str(), nullptr, BIN_BASE);
}
