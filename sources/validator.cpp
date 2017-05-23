/**
 * @file validator.cpp
 * The file containing the validator namespace implementation.
 */
#include <string>
#include <regex>
#include "../headers/enums.h"
#include "../headers/Error.h"
#include "../headers/Line.h"
#include "../headers/validator.h"
#include "../headers/strutil.h"
#include "../headers/InstructionInfo.h"
#include "../headers/DirectiveInfo.h"
#include "../headers/OperationTable.h"
#include "../headers/DirectiveTable.h"

const std::regex labelRegex("^[a-zA-Z]{1}[a-zA-Z0-9]{0,5}$");
const std::regex operandRegex("^[a-zA-Z]{1}[a-zA-Z0-9]{0,5}(?:,X)?$");
const std::regex operationRegex("^[a-zA-Z]{1,6}$");
const std::regex hexLiteralRegex("^[=]?(?:[Xx]'[0-9A-Fa-f]+')$");
const std::regex charLiteralRegex("^[=]?(?:[Cc]'[^']+?')$");
const std::regex decLiteralRegex("^=[Ww]'[-+]?[0-9]+'$");
//const std::regex literalRegex("^(?:[Xx]'[0-9A-Fa-f]+')|(?:[Cc]'[^']+?')$");

const int COMMENT_LINE_LENGTH = 30;

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
bool isValidLabel(std::string label) {
    return (label.empty() || strutil::matches(label, labelRegex)) && !(OperationTable::getInstance()->contains(label)
            || DirectiveTable::getInstance()->contains(label));
}

/**
 * Checks whether an operation is valid or not. returns true in these cases:
 * <ul>
 * <li> operation matches operation regex.</li>
 * <li> operation matches a reserved keyword for instructions or directives.</li>
 * </ul>
 * @param operation - operation to be checked passed in the form of string.
 * @return true if it is a valid operation.
 */
bool isValidOperation(std::string operation) {
    return strutil::matches(operation, operationRegex) &&
           (OperationTable::getInstance()->contains(operation) ||
            DirectiveTable::getInstance()->contains(operation));
}

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
bool isValidOperand(std::string operand) {
    return (operand.empty() || strutil::matches(operand, operandRegex) || strutil::matches(operand, hexLiteralRegex)
           || strutil::matches(operand, charLiteralRegex) || strutil::matches(operand, decLiteralRegex))
            && !(OperationTable::getInstance()->contains(operand) || DirectiveTable::getInstance()->contains(operand))
            || strutil::isValidInteger(operand) || strutil::isValidHexadecimal(operand);
}

/**
 * Checks whether a comment is valid or not. returns true in these cases:
 * <ul>
 * <li> comment's size is less than or equal 30 bytes.</li>
 * </ul>
 * @param comment - comment to be checked passed in the form of string.
 * @return true if it is a valid comment.
 */
bool isValidComment(std::string comment) {
    return comment.size() <= COMMENT_LINE_LENGTH;
}

void validator::validateLine(Line &line) {
    if (!isValidLabel(line.label)) {
        throw new Error(ErrorType::INVALID_LABEL, line.label);
    } else if (!isValidOperation(line.operation)) {
        throw new Error(ErrorType::UNSUPPORTED_OPERATION, line.operation);
    } else if (!isValidOperand(line.operand)) {
        throw new Error(ErrorType::INVALID_OPERAND, line.operand);
    } else if (!isValidComment(line.comment)) {
        throw new Error(ErrorType::LONG_COMMENT, std::to_string(line.comment.size()));
    }
}

void validator::validateFormat(Line &line) {
    switch (line.lineFormat) {
        case ONE:
            if (line.operand != "")
                throw new Error(ErrorType::INVALID_FORMAT, line.operand);
            break;
        case TWO:
            //Register-to-register operations... Not implemented
            //since their are no supported register-to-register operations in SIC.
            break;
        case THREE:
            if (line.operand == "")
                throw new Error(ErrorType::INVALID_FORMAT, "Missing Operand");
            break;
        case FOUR:
            //This will never happen though since the "+OP" operations
            // won't pass the regex check at anytime since they are not supported in SIC.
            //Mainly this passed error cause is just relevant for one of the two essential conditions.
            if (line.operation[0] != '+' || line.operand == "")
                throw new Error(ErrorType::INVALID_FORMAT, "Missing Operand");
            break;
        default:
            break;
    }
}
