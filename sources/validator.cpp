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
const std::regex literalRegex("^(?:[Xx]'[0-9A-Fa-f]+')|(?:[Cc]'[^']+?')$");

const int COMMENT_LINE_LENGTH = 30;

bool isValidLabel(std::string label) {
    return (label.empty() || strutil::matches(label, labelRegex)) && !(OperationTable::getInstance()->contains(label)
            || DirectiveTable::getInstance()->contains(label));
}

bool isValidOperation(std::string operation) {
    return strutil::matches(operation, operationRegex) &&
           (OperationTable::getInstance()->contains(operation) ||
            DirectiveTable::getInstance()->contains(operation));
}

bool isValidOperand(std::string operand) {
    try {
        std::stoi(operand);
        return true;
    } catch(std::invalid_argument ex) {
        try {
            std::stoi(operand, 0, 16);
            return true;
        } catch (std::invalid_argument ex2) {

        } catch (std::out_of_range ex2) {

        }
    } catch(std::out_of_range ex) {

    }
    return (operand.empty() || strutil::matches(operand, operandRegex) || strutil::matches(operand, literalRegex))
            && !(OperationTable::getInstance()->contains(operand) || DirectiveTable::getInstance()->contains(operand));
}

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
            // won't pass the regex check at anytime since it's not supported in SIC.
            if (line.operation[0] != '+' || line.operand == "")
                throw new Error(ErrorType::INVALID_FORMAT, "Missing Operand");
            break;
        default:
            break;
    }
}
