//
// Created by Mohammed Abdelbarry on 01-May-17.
//

#ifndef SIC_XE_ASSEMBLER_DIRECTIVE_INFO_H
#define SIC_XE_ASSEMBLER_DIRECTIVE_INFO_H

#include "enums.h"
#include "Line.h"
#include <functional>

class DirectiveInfo {

public:
    Label label;
    std::function<void(int&, Line)> execute;
};
#endif //SIC_XE_ASSEMBLER_DIRECTIVE_INFO_H
