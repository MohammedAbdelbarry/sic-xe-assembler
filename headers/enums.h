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

enum ErrorType {
    INVALID_LABEL,
    UNSUPPORTED_OPERATION,
    DUPLICATE_START,
    INVALID_OPERAND,
    INVALID_FORMAT,
    EXTRA_CHARACTERS_AT_EOL
};

enum MnemonicType {
    INSTRUCTION,
    DIRECTIVE
};

enum LineType {
    ASSEMBLY_STATEMENT,
    COMMENT
};
#endif //PROJECT_ENUMS_H
