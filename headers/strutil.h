//
// Created by salem.harby on 05/04/2017.
//

#ifndef SIC_XE_ASSEMBLER_STRUTIL_H
#define SIC_XE_ASSEMBLER_STRUTIL_H


namespace strutil {
    std::vector<std::string> split(std::string str, std::regex &regex, int splitsNumber = -1);
    bool matches(std::string str, std::regex regex);
    bool endsWith(std::string const &value, std::string const &ending);
    bool beginWith(std::string const &value, std::string const &beginning);
    void addHex(std::ostringstream& stringStream, int decimalNumber, int numChars);
    std::string parseCharLiteral(std::string charLiteral);
    bool isCharLiteral(std::string charLiteral);
    std::string toUpper(std::string str);
};


#endif //SIC_XE_ASSEMBLER_STRUTIL_H
