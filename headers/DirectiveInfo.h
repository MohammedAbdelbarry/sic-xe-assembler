/**
 * @file DirectiveInfo.h
 * Represents info for each directive (label, function that updates location counter).
 */

#ifndef SIC_XE_ASSEMBLER_DIRECTIVE_INFO_H
#define SIC_XE_ASSEMBLER_DIRECTIVE_INFO_H

#include <functional>
#include "enums.h"
#include "Line.h"
#include "SymbolTable.h"

/**
 * Represents info for each directive, contains label for the directive and a<br>
 * function that updtes location counter accordingly.
 */
class DirectiveInfo {

public:
	/**
	 * Label of the corresponding directive.
	 */
    Label label;
    /**
     * A function that is defined for each directive. Takes in the location<br>
     * counter and updates it accordingly based on the line passed to the function.
     */
    std::function<void(int&, Line, SymbolTable&)> execute;
};
#endif //SIC_XE_ASSEMBLER_DIRECTIVE_INFO_H
