/**
 * @file InstructionInfo.h
 * A file containing the declaration of the InstructionInfo class.
 */
#ifndef PROJECT_INSTRUCTION_INFO_H
#define PROJECT_INSTRUCTION_INFO_H

#include "enums.h"
#include <vector>

/**
 * A class containing some information about the instruction.
 */
class InstructionInfo {

public:
    /**
     * The opCode of the instruction.
     */
    unsigned char opCode;
    /**
     * An enum representing the existence of label in
     * the instruction.
     */
    Label label;
    /**
     * The supported formats of the instruction.
     */
    std::vector<InstructionFormat> supportedFormats;
};
#endif //PROJECT_INSTRUCTION_INFO_H
