//
// Created by Mohammed Abdelbarry on 01-May-17.
//

#ifndef SIC_XE_ASSEMBLER_DIRECTIVE_INFO_H
#define SIC_XE_ASSEMBLER_DIRECTIVE_INFO_H

#include "enums.h"

class directive_info {

public:
    Label label;
    Operand operand;
    OperandType operandType;
};
#endif //SIC_XE_ASSEMBLER_DIRECTIVE_INFO_H
