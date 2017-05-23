/**
 * @file OperationTable.cpp
 * The file containing the operation table class implementation.
 */
#include <string>
#include <map>
#include <vector>
#include <regex>
#include "../headers/InstructionInfo.h"
#include "../headers/OperationTable.h"
#include "../headers/strutil.h"

OperationTable *OperationTable::instance = nullptr;

OperationTable::OperationTable() {
    initOpTable();
}

OperationTable* OperationTable::getInstance() {
    if(instance == nullptr)
        instance = new OperationTable;
    return instance;
}

/**
 * Initializes the operation table
 */
void OperationTable::initOpTable() {
    std::string opName;
    InstructionInfo info;

    opName = "ADD";
    info = InstructionInfo();
    info.opCode = 0x18;
    info.label = Label::OPTIONAL;
    info.supportedFormats.push_back(InstructionFormat::THREE);
    info.supportedFormats.push_back(InstructionFormat::FOUR);
    opTable[opName] = info;

    opName = "SUB";
    info = InstructionInfo();
    info.opCode = 0x1C;
    info.label = Label::OPTIONAL;
    info.supportedFormats.push_back(InstructionFormat::THREE);
    info.supportedFormats.push_back(InstructionFormat::FOUR);
    opTable[opName] = info;

    opName = "MUL";
    info = InstructionInfo();
    info.opCode = 0x20;
    info.label = Label::OPTIONAL;
    info.supportedFormats.push_back(InstructionFormat::THREE);
    info.supportedFormats.push_back(InstructionFormat::FOUR);
    opTable[opName] = info;

    opName = "DIV";
    info = InstructionInfo();
    info.opCode = 0x24;
    info.label = Label::OPTIONAL;
    info.supportedFormats.push_back(InstructionFormat::THREE);
    info.supportedFormats.push_back(InstructionFormat::FOUR);
    opTable[opName] = info;

    opName = "AND";
    info = InstructionInfo();
    info.opCode = 0x40;
    info.label = Label::OPTIONAL;
    info.supportedFormats.push_back(InstructionFormat::THREE);
    info.supportedFormats.push_back(InstructionFormat::FOUR);
    opTable[opName] = info;

    opName = "OR";
    info = InstructionInfo();
    info.opCode = 0x44;
    info.label = Label::OPTIONAL;
    info.supportedFormats.push_back(InstructionFormat::THREE);
    info.supportedFormats.push_back(InstructionFormat::FOUR);
    opTable[opName] = info;

    opName = "COMP";
    info = InstructionInfo();
    info.opCode = 0x28;
    info.label = Label::OPTIONAL;
    info.supportedFormats.push_back(InstructionFormat::THREE);
    info.supportedFormats.push_back(InstructionFormat::FOUR);
    opTable[opName] = info;

    opName = "LDA";
    info = InstructionInfo();
    info.opCode = 0x00;
    info.label = Label::OPTIONAL;
    info.supportedFormats.push_back(InstructionFormat::THREE);
    info.supportedFormats.push_back(InstructionFormat::FOUR);
    opTable[opName] = info;

    opName = "LDCH";
    info = InstructionInfo();
    info.opCode = 0x50;
    info.label = Label::OPTIONAL;
    info.supportedFormats.push_back(InstructionFormat::THREE);
    info.supportedFormats.push_back(InstructionFormat::FOUR);
    opTable[opName] = info;

    opName = "LDL";
    info = InstructionInfo();
    info.opCode = 0x08;
    info.label = Label::OPTIONAL;
    info.supportedFormats.push_back(InstructionFormat::THREE);
    info.supportedFormats.push_back(InstructionFormat::FOUR);
    opTable[opName] = info;

    opName = "LDX";
    info = InstructionInfo();
    info.opCode = 0x04;
    info.label = Label::OPTIONAL;
    info.supportedFormats.push_back(InstructionFormat::THREE);
    info.supportedFormats.push_back(InstructionFormat::FOUR);
    opTable[opName] = info;

    opName = "TD";
    info = InstructionInfo();
    info.opCode = 0xE0;
    info.label = Label::OPTIONAL;
    info.supportedFormats.push_back(InstructionFormat::THREE);
    info.supportedFormats.push_back(InstructionFormat::FOUR);
    opTable[opName] = info;

    opName = "RD";
    info = InstructionInfo();
    info.opCode = 0xD8;
    info.label = Label::OPTIONAL;
    info.supportedFormats.push_back(InstructionFormat::THREE);
    info.supportedFormats.push_back(InstructionFormat::FOUR);
    opTable[opName] = info;

    opName = "WD";
    info = InstructionInfo();
    info.opCode = 0xDC;
    info.label = Label::OPTIONAL;
    info.supportedFormats.push_back(InstructionFormat::THREE);
    info.supportedFormats.push_back(InstructionFormat::FOUR);
    opTable[opName] = info;

    opName = "TIX";
    info = InstructionInfo();
    info.opCode = 0x2C;
    info.label = Label::OPTIONAL;
    info.supportedFormats.push_back(InstructionFormat::THREE);
    info.supportedFormats.push_back(InstructionFormat::FOUR);
    opTable[opName] = info;

    opName = "STA";
    info = InstructionInfo();
    info.opCode = 0x0C;
    info.label = Label::OPTIONAL;
    info.supportedFormats.push_back(InstructionFormat::THREE);
    info.supportedFormats.push_back(InstructionFormat::FOUR);
    opTable[opName] = info;

    opName = "STCH";
    info = InstructionInfo();
    info.opCode = 0x54;
    info.label = Label::OPTIONAL;
    info.supportedFormats.push_back(InstructionFormat::THREE);
    info.supportedFormats.push_back(InstructionFormat::FOUR);
    opTable[opName] = info;

    opName = "STL";
    info = InstructionInfo();
    info.opCode = 0x14;
    info.label = Label::OPTIONAL;
    info.supportedFormats.push_back(InstructionFormat::THREE);
    info.supportedFormats.push_back(InstructionFormat::FOUR);
    opTable[opName] = info;

    opName = "STX";
    info = InstructionInfo();
    info.opCode = 0x10;
    info.label = Label::OPTIONAL;
    info.supportedFormats.push_back(InstructionFormat::THREE);
    info.supportedFormats.push_back(InstructionFormat::FOUR);
    opTable[opName] = info;

    opName = "J";
    info = InstructionInfo();
    info.opCode = 0x3C;
    info.label = Label::OPTIONAL;
    info.supportedFormats.push_back(InstructionFormat::THREE);
    info.supportedFormats.push_back(InstructionFormat::FOUR);
    opTable[opName] = info;

    opName = "JEQ";
    info = InstructionInfo();
    info.opCode = 0x30;
    info.label = Label::OPTIONAL;
    info.supportedFormats.push_back(InstructionFormat::THREE);
    info.supportedFormats.push_back(InstructionFormat::FOUR);
    opTable[opName] = info;

    opName = "JGT";
    info = InstructionInfo();
    info.opCode = 0x34;
    info.label = Label::OPTIONAL;
    info.supportedFormats.push_back(InstructionFormat::THREE);
    info.supportedFormats.push_back(InstructionFormat::FOUR);
    opTable[opName] = info;

    opName = "JLT";
    info = InstructionInfo();
    info.opCode = 0x38;
    info.label = Label::OPTIONAL;
    info.supportedFormats.push_back(InstructionFormat::THREE);
    info.supportedFormats.push_back(InstructionFormat::FOUR);
    opTable[opName] = info;

    opName = "JSUB";
    info = InstructionInfo();
    info.opCode = 0x48;
    info.label = Label::OPTIONAL;
    info.supportedFormats.push_back(InstructionFormat::THREE);
    info.supportedFormats.push_back(InstructionFormat::FOUR);
    opTable[opName] = info;

    opName = "RSUB";
    info = InstructionInfo();
    info.opCode = 0x4C;
    info.label = Label::OPTIONAL;
    info.supportedFormats.push_back(InstructionFormat::ONE);
    opTable[opName] = info;
}

bool OperationTable::contains(std::string operation) {
    return OperationTable::opTable.find(strutil::toUpper(operation)) != OperationTable::opTable.end();
}

InstructionInfo OperationTable::getInfo(std::string operation) {
    return OperationTable::opTable[strutil::toUpper(operation)];
}
