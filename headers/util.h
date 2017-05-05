//
// Created by Mohamed A.Tolba on 5/4/2017.
//

#ifndef SIC_XE_ASSEMBLER_UTIL_H
#define SIC_XE_ASSEMBLER_UTIL_H


namespace util {

    namespace Hexadecimal {
        std::string toBin(std::string number);
        int toDec(std::string number);
        std::string parseHexadecimalLiteral(std::string hexLiteral);
    }

    namespace Decimal {
        std::string toString(int number);
        std::string toBin(int number);
        std::string toHex(int number);
    }

    namespace Binary {
        int toDec(std::string number);
        std::string toHex(std::string number);
    }
}

#endif //SIC_XE_ASSEMBLER_UTIL_H
