//
// Created by Mohammed Abdelbarry on 01-May-17.
//

#ifndef PROJECT_ENUMS_H
#define PROJECT_ENUMS_H

enum Label {
    NONE,
    OPTIONAL,
    MUST
};

enum InstructionFormat {
    ONE,
    TWO,
    THREE,
    FOUR
};

enum ErrorMessage {
    INVALID_LABEL,
    UNSUPPORTED_OPERATION,
    UNDEFINED_OPERAND,
    INVALID_FORMAT
};

enum MnemonicType {
    INSTRUCTION,
    DIRECTIVE
};
#endif //PROJECT_ENUMS_H
