/**
 * @file LiteralInfo.h
 * A file containing the declaration of the LiteralInfo class.
 */
#ifndef SIC_XE_ASSEMBLER_LITERALINFO_H
#define SIC_XE_ASSEMBLER_LITERALINFO_H

#include <string>
#include "enums.h"
/**
 * A class containing some information about the literal.
 */
class LiteralInfo {

public:
    /**
     * The actual value of the literal.
     */
    std::string literal;
    /**
     * An enum representing the type of directive that should be used in resolving
     * this literal.
     */
    LiteralDirective literalDirective;
    /**
     * A boolean flag that indicates whether this literal had been resolved before or not.
     */
    bool resolved;
    /**
     * The label string which will replace this literal in SIC assembly statements whenever this literal
     * or its alternatives are used.
     */
    std::string label;
};
#endif //SIC_XE_ASSEMBLER_LITERALINFO_H