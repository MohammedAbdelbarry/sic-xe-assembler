/**
 * @file DirectiveTable.cpp
 * Directive table implementation.
 */

#include <functional>
#include <iostream>
#include <map>
#include <vector>
#include <regex>
#include "../headers/enums.h"
#include "../headers/Error.h"
#include "../headers/numutil.h"
#include "../headers/strutil.h"
#include "../headers/DirectiveInfo.h"
#include "../headers/DirectiveTable.h"

/**
 * Singleton instance.
 */
DirectiveTable *DirectiveTable::instance = nullptr;

/**
 * Constructs directive table.
 */
DirectiveTable::DirectiveTable() {
    initDirTable();
}

/**
 * Gets the singleton instance of directive table.
 * @return [instance to directive table].
 */
DirectiveTable* DirectiveTable::getInstance() {
    if (instance == nullptr)
        instance = new DirectiveTable();
    return instance;
}

/**
 * Initializes directive table (lists all supported directives):
 * <ul>
 * <li>START</li>
 * <li>BYTE</li>
 * <li>WORD</li>
 * <li>RESW</li>
 * <li>RESB</li>
 * <li>END</li>
 * </ul>
 */
void DirectiveTable::initDirTable() {
    std::string dirName;
    DirectiveInfo info;
    const char HEX_BASE = 16;
    const int SIC_MAX_MEMORY = 1 << 15;
    const int SIC_MAX_WORD = 1 << 24;
    dirName = "START";
    info.label = Label::OPTIONAL;
    info.execute = [](int &locCtr, Line line) {
        try {
            int pos = std::stoi(line.operand, 0, HEX_BASE);
            if (pos < 0 || pos >= SIC_MAX_MEMORY || !(strutil::isValidInteger(line.operand)
                                                     || strutil::isValidHexadecimal(line.operand)))
                throw new Error(ErrorType::INVALID_OPERAND, line.operand);
            locCtr = pos;
        } catch(std::invalid_argument ex) {
            throw new Error(ErrorType::INVALID_OPERAND, line.operand);
        } catch(std::out_of_range ex) {
            throw new Error(ErrorType::INVALID_OPERAND, line.operand);
        }
    };
    dirTable[dirName] = info;

    dirName = "BYTE";
    info.execute = [](int &locCtr, Line line) {
        if (strutil::isCharLiteral(line.operand)) {
            int literalLength = line.operand.length() - 3;
            locCtr += literalLength;
        } else if (numutil::Hexadecimal::isHexLiteral(line.operand)){
            int literalLength = line.operand.length() - 3;
            locCtr += (literalLength / 2 + ((literalLength % 2) != 0));
        } else {
            throw new Error(ErrorType::INVALID_OPERAND, line.operand);
        }
    };
    dirTable[dirName] = info;

    dirName = "WORD";
    info.execute = [](int &locCtr, Line line) {
        if (strutil::isCharLiteral(line.operand)) {
            int literalLength = line.operand.length() - 3;
            locCtr += 3 * (literalLength / 3 + ((literalLength % 3) != 0));
        } else if (numutil::Hexadecimal::isHexLiteral(line.operand)){
            int literalLength = line.operand.length() - 3;
            locCtr += 3 * (literalLength / 6 + ((literalLength % 6) != 0));
        } else {
            if (strutil::isValidInteger(line.operand) || strutil::isValidHexadecimal(line.operand)) {
                locCtr += 3;
            } else {
                throw new Error(ErrorType::INVALID_OPERAND, line.operand);
            }
        }
    };
    dirTable[dirName] = info;

    dirName = "RESB";
    info.execute = [](int &locCtr, Line line) {
        try {
            int count = std::stoi(line.operand);
            if (count < 0 || count >= SIC_MAX_MEMORY || !strutil::isValidInteger(line.operand))
                throw new Error(ErrorType::INVALID_OPERAND, line.operand);
            locCtr += count;
        } catch(std::invalid_argument ex) {
            throw new Error(ErrorType::INVALID_OPERAND, line.operand);
        } catch(std::out_of_range ex) {
            throw new Error(ErrorType::INVALID_OPERAND, line.operand);
        }
    };
    dirTable[dirName] = info;

    dirName = "RESW";
    info.execute = [](int &locCtr, Line line) {
        try {
            int count = 3 * std::stoi(line.operand);
            if (count < 0 || count >= SIC_MAX_MEMORY || !strutil::isValidInteger(line.operand))
                throw new Error(ErrorType::INVALID_OPERAND, line.operand);
            locCtr += count;
        } catch(std::invalid_argument ex) {
            throw new Error(ErrorType::INVALID_OPERAND, line.operand);
        } catch(std::out_of_range ex) {
            throw new Error(ErrorType::INVALID_OPERAND, line.operand);
        }
    };
    dirTable[dirName] = info;

    dirName = "END";
    info.execute = [](int &locCtr, Line line) {
        try {
            int pos = std::stoi(line.operand, 0, HEX_BASE);
            if (pos < 0 || pos >= SIC_MAX_MEMORY || !(strutil::isValidInteger(line.operand)
                                                      || strutil::isValidHexadecimal(line.operand)))
                throw new Error(ErrorType::INVALID_OPERAND, line.operand);
            locCtr = pos;
        } catch(std::invalid_argument ex) {
            throw new Error(ErrorType::INVALID_OPERAND, line.operand);
        } catch(std::out_of_range ex) {
            throw new Error(ErrorType::INVALID_OPERAND, line.operand);
        }
    };
    dirTable[dirName] = info;
}

/**
 * Checks if directive table contains a certain directive (case insensitive).
 * @param  directive [Directive to be checked for the bottom of its existence in this futile universe.]
 * @return           [True if directive table contains this directive.]
 */
bool DirectiveTable::contains(std::string directive) {
    return dirTable.find(strutil::toUpper(directive)) != dirTable.end();
}

/**
 * Gets {@link DirectiveInfo.h} corresponding to each directive.
 * @param  directive [Directive that has the required corresponding info.]
 * @return           [description]
 */
DirectiveInfo DirectiveTable::getInfo(std::string directive) {
    return dirTable[strutil::toUpper(directive)];
}