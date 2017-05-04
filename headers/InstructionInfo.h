//
// Created by Mohammed Abdelbarry on 01-May-17.
//
#ifndef PROJECT_INSTRUCTION_INFO_H
#define PROJECT_INSTRUCTION_INFO_H


#include <vector>
#include "enums.h"

class InstructionInfo {

public:
    unsigned char opCode;
    Label label;
    std::vector<InstructionFormat> supportedFormats;
};
#endif //PROJECT_INSTRUCTION_INFO_H
