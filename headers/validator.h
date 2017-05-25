/**
 * @file validator.h
 * The file containing the validator namespace declaration.
 */
#ifndef SIC_XE_ASSEMBLER_VALIDATOR_H
#define SIC_XE_ASSEMBLER_VALIDATOR_H

#include "Line.h"
#include <string>

/*!
*  \addtogroup Validator
*  @{
*/
//! A namespace which is dedicated to support some validation functions.
namespace validator {
    /**
     * Checks whether a line's format is valid or not. doesn't throw an error if relevant cases are met:
     * <ul>
     * <li> line's format is format 1 and line's operand is empty.</li>
     * <li> line's format is format 2 (Not supported yet).</li>
     * <li> line's format is format 3 and line's operand isn't empty.</li>
     * <li> line's format is format 4 and line's operand isn't empty and its operation doesn't start with "+" also.</li>
     * </ul>
     * @param line - line to be checked passed in the form of string
     */
    void validateFormat(Line &line);

    /**
     * Checks whether a label is valid or not. returns true in these cases:
     * <ul>
     * <li> label is empty.</li>
     * <li> label matches label regex.</li>
     * <li> label doesn't match a reserved keyword for instructions or directives.</li>
     * </ul>
     * @param label - label to be checked passed in the form of string.
     * @return true if it is a valid label.
     */
    bool isValidLabel(std::string label);

    /**
     * Checks whether an operation is valid or not. returns true in these cases:
     * <ul>
     * <li> operation matches operation regex.</li>
     * <li> operation matches a reserved keyword for instructions or directives.</li>
     * </ul>
     * @param operation - operation to be checked passed in the form of string.
     * @return true if it is a valid operation.
     */
    bool isValidOperation(std::string operation);

    /**
     * Checks whether an operand is valid or not. returns true in these cases:
     * <ul>
     * <li> operand is a decimal or a hexadecimal integer.</li>
     * <li> operand is empty.</li>
     * <li> operand matches operand regex or literal regex.</li>
     * <li> operand doesn't match a reserved keyword for instructions or directives.</li>
     * </ul>
     * @param operand - operand to be checked passed in the form of string.
     * @return true if it is a valid operand.
     */
    bool isValidOperand(std::string operand);

    /**
     * Checks whether a comment is valid or not. returns true in these cases:
     * <ul>
     * <li> comment's size is less than or equal 30 bytes.</li>
     * </ul>
     * @param comment - comment to be checked passed in the form of string.
     * @return true if it is a valid comment.
     */
    bool isValidComment(std::string comment);

};


#endif //SIC_XE_ASSEMBLER_VALIDATOR_H
