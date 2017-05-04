//
// Created by salem.harby on 05/04/2017.
//

#ifndef SIC_XE_ASSEMBLER_STRUTIL_H
#define SIC_XE_ASSEMBLER_STRUTIL_H


namespace strutil {
    std::vector<std::string> split(std::string str, std::regex regex);
    bool matches(std::string str, std::regex regex);
    void addHex(std::ostringstream& stringStream, int decimalNumber, int numChars);
};


#endif //SIC_XE_ASSEMBLER_STRUTIL_H
