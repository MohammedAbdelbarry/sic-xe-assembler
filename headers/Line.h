//
// Created by Mohamed A.Tolba on 5/1/2017.
//

#ifndef SIC_XE_ASSEMBLER_LINE_H
#define SIC_XE_ASSEMBLER_LINE_H

#include <string>

class Line {

public:
    Line(std::string label, std::string operation, std::string operand);
    std::string label;
    std::string operation;
    std::string operand;
};


#endif //SIC_XE_ASSEMBLER_LINE_H