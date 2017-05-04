#include <string>
#include <regex>
#include "../headers/enums.h"
#include "../headers/Line.h"
#include "../headers/validator.h"
#include "../headers/strutil.h"
#include "../headers/InstructionInfo.h"
#include "../headers/DirectiveInfo.h"
#include "../headers/OperationTable.h"
#include "../headers/DirectiveTable.h"

const std::regex labelRegex("^[a-zA-Z]{1}[a-zA-Z0-9]{0,7}$");
const std::regex operationRegex("^[a-zA-Z]{1,6}$");
const std::regex literalRegex("^(?:=[Xx]'[+-]?[0-9A-Fa-f]+')|(?:=[Cc]'[^']+?')$");

bool isValidLabel(std::string label) {
    return strutil::matches(label, labelRegex);
}

bool isValidOperation(std::string operation) {
    return strutil::matches(operation, operationRegex) &&
           (OperationTable::getInstance()->contains(operation) ||
            DirectiveTable::getInstance()->contains(operation));
}

bool isValidOperand(std::string operand) {
    return strutil::matches(operand, literalRegex) || strutil::matches(operand, labelRegex);
}

bool validator::isValidLine(Line line) {
    return isValidLabel(line.label) && isValidOperation(line.operation)
           && isValidOperand(line.operand);
}
