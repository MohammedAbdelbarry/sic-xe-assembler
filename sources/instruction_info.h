//
// Created by Mohammed Abdelbarry on 01-May-17.
//
#include <vector>
#include "enums.h"
#ifndef PROJECT_INSTRUCTION_INFO_H
#define PROJECT_INSTRUCTION_INFO_H

class instruction_info {

public:
    unsigned char opCode;
    Label label;
    std::vector<InstructionFormat> supportedFormats;
    Operand operand;
    OperandType operandType;
};
#endif //PROJECT_INSTRUCTION_INFO_H
