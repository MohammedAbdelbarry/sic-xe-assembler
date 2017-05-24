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
#include "../headers/SymbolTable.h"
#include <regex>

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

std::regex whiteSpaceRegex("\\s+");
std::regex addSubRegex("[+-]");
int evaluate(std::string operand, SymbolTable &symTab, int locCtr);

/**
 * Initializes directive table (lists all supported directives):
 * <ul>
 * <li>START</li>
 * <li>BYTE</li>
 * <li>WORD</li>
 * <li>RESW</li>
 * <li>RESB</li>
 * <li>EQU</li>
 * <li>LTORG</li>
 * <li>ORG</li>
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
    info.execute = [](int &locCtr, Line line, SymbolTable &symTab) {
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
    info.execute = [](int &locCtr, Line line, SymbolTable &symTab) {
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
    info.execute = [](int &locCtr, Line line, SymbolTable &symTab) {
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
    info.execute = [](int &locCtr, Line line, SymbolTable &symTab) {
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
    info.execute = [](int &locCtr, Line line, SymbolTable &symTab) {
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

    dirName = "EQU";
    info.execute = [](int &locCtr, Line line, SymbolTable &symTab) {
        std::string label = strutil::trim(line.label);
        if (label == "" || label == "*")
            throw new Error(ErrorType::INVALID_LABEL, line.label);
        int address = evaluate(line.operand, symTab, locCtr);
        if (address < 0 || address >= SIC_MAX_MEMORY)
            throw new Error(ErrorType::INVALID_OPERAND, line.operand);
        symTab.push(line.label, address);
    };
    dirTable[dirName] = info;

    dirName = "END";
    info.execute = [](int &locCtr, Line line, SymbolTable &symTab) {
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

    dirName = "ORG";
    info.label = Label::OPTIONAL;
    info.execute = [](int &locCtr, Line line, SymbolTable &symTab) {
        static int prevLocCtr = -1;
        if(line.operand.empty()) {
            if(prevLocCtr != -1) {
                locCtr = prevLocCtr;
            } else {
            }
            return;
        }
        prevLocCtr = locCtr;
        int address = evaluate(line.operand, symTab, locCtr);
        if (address < 0 || address >= SIC_MAX_MEMORY)
            throw new Error(ErrorType::INVALID_OPERAND, line.operand);
        locCtr = address;
        /*
         * TODO: Modify the locctr and store the original value.
         * ORG requires some special handling in pass1 since the operand is optional
         * and it requires some communication with the assembler to store the previous value of the locctr
         * or revert to it (NOTE: this can be done with a static variable that stores the previous value of the locctr
         * and reverts the locctr to it if the operand is empty)
         */
        //TODO: search the symbol table for the operand and modify the location counter accordingly.
    };
    dirTable[dirName] = info;

    dirName = "LTORG";
    info.label = Label::NONE; // Assuming it can't have a label.
    info.execute = [](int &locCtr, Line line, SymbolTable &symTab) {
        if (!line.label.empty()) {
            throw new Error(ErrorType::INVALID_LABEL, line.label);
        } else if (!line.operand.empty()) {
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

int evaluate(std::string operand, SymbolTable &symTab, int locCtr) {
    std::vector<std::string> ops;
    operand = std::regex_replace(operand, addSubRegex, " $& ");
    for (std::string x : strutil::split(operand, whiteSpaceRegex, 2))
        ops.push_back(strutil::trim(x));
    if (!(ops.size() == 1 || ops.size() == 3))
        throw new Error(ErrorType::INVALID_OPERAND, operand);
    std::function<int(std::string)> f = [operand, &symTab, locCtr](std::string splitOperand) {
        int res = 0;
        try {
            if (strutil::isValidInteger(splitOperand)) {
                res = std::stoi(splitOperand);
            } else if (strutil::isValidHexadecimal(splitOperand)) {
                res = std::stoi(splitOperand, 0, 16);
            } else if (splitOperand == "*") {
                res = locCtr;
            } else {
                if (!symTab.contains(splitOperand))
                    throw new Error(ErrorType::INVALID_OPERAND, operand);
                res = symTab.getAddress(splitOperand);
            }
        } catch (...) {
            throw new Error(ErrorType::INVALID_OPERAND, operand);
        }
        return res;
    };
    int address = f(ops[0]);
    if (ops.size() == 3)
        address += ops[1] == "+" ? f(ops[2]) : -1 * f(ops[2]);
    return address;
}