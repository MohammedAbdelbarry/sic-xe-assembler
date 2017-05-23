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

std::regex addSubRegex("\\s+");

int evaluate(std::string operand, SymbolTable symTab);

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
    info.execute = [](int &locCtr, Line line, SymbolTable &symTab) {
        try {
            int pos = std::stoi(line.operand, 0, HEX_BASE);
            if (pos < 0 || pos >= SIC_MAX_MEMORY)
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
            try {
                int op = std::stoi(line.operand);
                if (op < -SIC_MAX_WORD || op >= SIC_MAX_WORD)
                    throw new Error(ErrorType::INVALID_OPERAND, line.operand);
                locCtr += 3;
            } catch(std::invalid_argument ex) {
                try {
                    int op = std::stoi(line.operand, 0, HEX_BASE);
                    if (op < -SIC_MAX_WORD || op >= SIC_MAX_WORD)
                        throw new Error(ErrorType::INVALID_OPERAND, line.operand);
                    locCtr += 3;
                } catch(std::invalid_argument ex) {
                    throw new Error(ErrorType::INVALID_OPERAND, line.operand);
                } catch(std::out_of_range ex) {
                    throw new Error(ErrorType::INVALID_OPERAND, line.operand);
                }
            } catch(std::out_of_range ex) {
                throw new Error(ErrorType::INVALID_OPERAND, line.operand);
            }
        }
    };
    dirTable[dirName] = info;

    dirName = "RESB";
    info.execute = [](int &locCtr, Line line, SymbolTable &symTab) {
        try {
            int count = std::stoi(line.operand);
            if (count < 0 || count >= SIC_MAX_MEMORY)
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
            if (count < 0 || count >= SIC_MAX_MEMORY)
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
        int address = evaluate(line.operand, symTab);
        if (address < 0 || address >= SIC_MAX_MEMORY)
            throw new Error(ErrorType::INVALID_OPERAND, line.operand);
        symTab.push(line.label, address);
    };
    dirTable[dirName] = info;

    dirName = "END";
    info.execute = [](int &locCtr, Line line, SymbolTable &symTab) {
        try {
            int pos = std::stoi(line.operand, 0, HEX_BASE);
            if (pos < 0 || pos >= SIC_MAX_MEMORY)
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

int evaluate(std::string operand, SymbolTable symTab) {
    std::vector<std::string> ops;
    for (std::string x : strutil::split(operand, addSubRegex, 1))
        ops.push_back(strutil::trim(x));
    if (!(ops.size() == 1 || ops.size() == 3))
        throw new Error(ErrorType::INVALID_OPERAND, operand);
    std::function<int(std::string)> f = [operand, &symTab](std::string operand) {
        int res = 0;
        try {
            res = std::stoi(operand);
        } catch (...) {
            if (!symTab.contains(operand))
                throw new Error(ErrorType::INVALID_OPERAND, operand);
            res = symTab.getAddress(operand);
        }
        return res;
    };
    int address = f(ops[0]);
    if (ops.size() == 3)
        address += ops[1] == "+" ? f(ops[2]) : -1 * f(ops[2]);
    return address;
}