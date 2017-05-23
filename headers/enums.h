/**
 * @file enums.h
 * A file containing collection of useful enums.
 */

#ifndef PROJECT_ENUMS_H
#define PROJECT_ENUMS_H
/**
 * An enum representing the existence or absence of label
 * in a SIC instruction.
 */
enum Label {
    NONE,
    OPTIONAL,
    MUST
};
/**
 * An enum representing the format of the SIC instruction.
 */
enum InstructionFormat {
    ONE,
    TWO,
    THREE,
    FOUR
};
/**
 * An enum representing the type of the error.
 */
enum ErrorType {
    INVALID_LABEL,
    UNSUPPORTED_OPERATION,
    DUPLICATE_START,
    INVALID_OPERAND,
    INVALID_FORMAT,
    LONG_COMMENT
};
/**
 * An enum representing the type of the mnemonic.
 */
enum MnemonicType {
    INSTRUCTION,
    DIRECTIVE
};
/**
 * An enum representing the type of the line.
 */
enum LineType {
    ASSEMBLY_STATEMENT,
    COMMENT
};
#endif //PROJECT_ENUMS_H
