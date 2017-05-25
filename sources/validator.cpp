/**
 * @file validator.cpp
 * The file containing the validator namespace implementation.
 */
#include "../headers/DirectiveTable.h"
#include "../headers/OperationTable.h"
#include "../headers/strutil.h"
#include "../headers/validator.h"

const std::regex labelRegex("^[a-zA-Z]{1}[a-zA-Z0-9]{0,5}$");
const std::regex operandRegex("^[a-zA-Z]{1}[a-zA-Z0-9]{0,5}(?:,X)?$");
const std::regex operationRegex("^[a-zA-Z]{1,6}$");
const std::regex hexLiteralRegex("^[=]?(?:[Xx]'[0-9A-Fa-f]+')$");
const std::regex charLiteralRegex("^[=]?(?:[Cc]'[^']+?')$");
const std::regex decLiteralRegex("^=[Ww]'[-+]?[0-9]+'$");
//const std::regex literalRegex("^(?:[Xx]'[0-9A-Fa-f]+')|(?:[Cc]'[^']+?')$");

const int COMMENT_LINE_LENGTH = 30;

bool validator::isValidLabel(std::string label) {
    return (label.empty() || strutil::matches(label, labelRegex)) && !(OperationTable::getInstance()->contains(label)
            || DirectiveTable::getInstance()->contains(label));
}

bool validator::isValidOperation(std::string operation) {
    return strutil::matches(operation, operationRegex) &&
           (OperationTable::getInstance()->contains(operation) ||
            DirectiveTable::getInstance()->contains(operation));
}

bool validator::isValidOperand(std::string operand) {
    return (operand.empty() || strutil::matches(operand, operandRegex) || strutil::matches(operand, hexLiteralRegex)
           || strutil::matches(operand, charLiteralRegex) || strutil::matches(operand, decLiteralRegex))
            && !(OperationTable::getInstance()->contains(operand) || DirectiveTable::getInstance()->contains(operand))
            || strutil::isValidInteger(operand) || strutil::isValidHexadecimal(operand);
}

bool validator::isValidComment(std::string comment) {
    return comment.size() <= COMMENT_LINE_LENGTH;
}

void validator::validateFormat(Line &line) {
    switch (line.lineFormat) {
        case ONE:
            if (line.operand != "")
                throw new Error(ErrorType::INVALID_FORMAT, line.operand);
            break;
        case TWO:
            //Register-to-register operations... Not implemented
            //since there are no supported register-to-register operations in SIC.
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
