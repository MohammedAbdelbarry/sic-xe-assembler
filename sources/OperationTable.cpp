//
// Created by Mohammed Abdelbarry on 01-May-17.
//

#include <string>
#include <map>
#include "../headers/InstructionInfo.h"
#include "../headers/OperationTable.h"

OperationTable *OperationTable::instance = nullptr;

OperationTable::OperationTable() {
    initOpTable();
}

OperationTable* OperationTable::getInstance() {
    if(instance == nullptr)
        instance = new OperationTable;
    return instance;
}

void OperationTable::initOpTable() {
    std::string opName;
    InstructionInfo info;

    opName = "ADD";
    info.opCode = 0x18;
    info.label = Label::OPTIONAL;
    info.supportedFormats.push_back(InstructionFormat::THREE);
    info.supportedFormats.push_back(InstructionFormat::FOUR);
    opTable[opName] = info;

    opName = "SUB";
    info.opCode = 0x1C;
    info.label = Label::OPTIONAL;
    info.supportedFormats.push_back(InstructionFormat::THREE);
    info.supportedFormats.push_back(InstructionFormat::FOUR);
    opTable[opName] = info;

    opName = "MUL";
    info.opCode = 0x20;
    info.label = Label::OPTIONAL;
    info.supportedFormats.push_back(InstructionFormat::THREE);
    info.supportedFormats.push_back(InstructionFormat::FOUR);
    opTable[opName] = info;

    opName = "DIV";
    info.opCode = 0x24;
    info.label = Label::OPTIONAL;
    info.supportedFormats.push_back(InstructionFormat::THREE);
    info.supportedFormats.push_back(InstructionFormat::FOUR);
    opTable[opName] = info;

    opName = "AND";
    info.opCode = 0x40;
    info.label = Label::OPTIONAL;
    info.supportedFormats.push_back(InstructionFormat::THREE);
    info.supportedFormats.push_back(InstructionFormat::FOUR);
    opTable[opName] = info;

    opName = "OR";
    info.opCode = 0x44;
    info.label = Label::OPTIONAL;
    info.supportedFormats.push_back(InstructionFormat::THREE);
    info.supportedFormats.push_back(InstructionFormat::FOUR);
    opTable[opName] = info;

    opName = "COMP";
    info.opCode = 0x28;
    info.label = Label::OPTIONAL;
    info.supportedFormats.push_back(InstructionFormat::THREE);
    info.supportedFormats.push_back(InstructionFormat::FOUR);
    opTable[opName] = info;

    opName = "LDA";
    info.opCode = 0x00;
    info.label = Label::OPTIONAL;
    info.supportedFormats.push_back(InstructionFormat::THREE);
    info.supportedFormats.push_back(InstructionFormat::FOUR);
    opTable[opName] = info;

    opName = "LDCH";
    info.opCode = 0x50;
    info.label = Label::OPTIONAL;
    info.supportedFormats.push_back(InstructionFormat::THREE);
    info.supportedFormats.push_back(InstructionFormat::FOUR);
    opTable[opName] = info;

    opName = "LDL";
    info.opCode = 0x08;
    info.label = Label::OPTIONAL;
    info.supportedFormats.push_back(InstructionFormat::THREE);
    info.supportedFormats.push_back(InstructionFormat::FOUR);
    opTable[opName] = info;

    opName = "LDX";
    info.opCode = 0x04;
    info.label = Label::OPTIONAL;
    info.supportedFormats.push_back(InstructionFormat::THREE);
    info.supportedFormats.push_back(InstructionFormat::FOUR);
    opTable[opName] = info;

    opName = "TD";
    info.opCode = 0xE0;
    info.label = Label::OPTIONAL;
    info.supportedFormats.push_back(InstructionFormat::THREE);
    info.supportedFormats.push_back(InstructionFormat::FOUR);
    opTable[opName] = info;

    opName = "RD";
    info.opCode = 0xD8;
    info.label = Label::OPTIONAL;
    info.supportedFormats.push_back(InstructionFormat::THREE);
    info.supportedFormats.push_back(InstructionFormat::FOUR);
    opTable[opName] = info;

    opName = "WD";
    info.opCode = 0xDC;
    info.label = Label::OPTIONAL;
    info.supportedFormats.push_back(InstructionFormat::THREE);
    info.supportedFormats.push_back(InstructionFormat::FOUR);
    opTable[opName] = info;

    opName = "TIX";
    info.opCode = 0x2C;
    info.label = Label::OPTIONAL;
    info.supportedFormats.push_back(InstructionFormat::THREE);
    info.supportedFormats.push_back(InstructionFormat::FOUR);
    opTable[opName] = info;

    opName = "STA";
    info.opCode = 0x0C;
    info.label = Label::OPTIONAL;
    info.supportedFormats.push_back(InstructionFormat::THREE);
    info.supportedFormats.push_back(InstructionFormat::FOUR);
    opTable[opName] = info;

    opName = "STCH";
    info.opCode = 0x54;
    info.label = Label::OPTIONAL;
    info.supportedFormats.push_back(InstructionFormat::THREE);
    info.supportedFormats.push_back(InstructionFormat::FOUR);
    opTable[opName] = info;

    opName = "STL";
    info.opCode = 0x14;
    info.label = Label::OPTIONAL;
    info.supportedFormats.push_back(InstructionFormat::THREE);
    info.supportedFormats.push_back(InstructionFormat::FOUR);
    opTable[opName] = info;

    opName = "STX";
    info.opCode = 0x10;
    info.label = Label::OPTIONAL;
    info.supportedFormats.push_back(InstructionFormat::THREE);
    info.supportedFormats.push_back(InstructionFormat::FOUR);
    opTable[opName] = info;

    opName = "J";
    info.opCode = 0x3C;
    info.label = Label::OPTIONAL;
    info.supportedFormats.push_back(InstructionFormat::THREE);
    info.supportedFormats.push_back(InstructionFormat::FOUR);
    opTable[opName] = info;

    opName = "JEQ";
    info.opCode = 0x30;
    info.label = Label::OPTIONAL;
    info.supportedFormats.push_back(InstructionFormat::THREE);
    info.supportedFormats.push_back(InstructionFormat::FOUR);
    opTable[opName] = info;

    opName = "JGT";
    info.opCode = 0x34;
    info.label = Label::OPTIONAL;
    info.supportedFormats.push_back(InstructionFormat::THREE);
    info.supportedFormats.push_back(InstructionFormat::FOUR);
    opTable[opName] = info;

    opName = "JLT";
    info.opCode = 0x38;
    info.label = Label::OPTIONAL;
    info.supportedFormats.push_back(InstructionFormat::THREE);
    info.supportedFormats.push_back(InstructionFormat::FOUR);
    opTable[opName] = info;

    opName = "JSUB";
    info.opCode = 0x48;
    info.label = Label::OPTIONAL;
    info.supportedFormats.push_back(InstructionFormat::THREE);
    info.supportedFormats.push_back(InstructionFormat::FOUR);
    opTable[opName] = info;

    opName = "RSUB";
    info.opCode = 0x4C;
    info.label = Label::OPTIONAL;
    info.supportedFormats.push_back(InstructionFormat::ONE);
    opTable[opName] = info;
}

bool OperationTable::contains(std::string operation) {
    return OperationTable::opTable.find(operation) != OperationTable::opTable.end();
}

InstructionInfo OperationTable::getInfo(std::string operation) {
    return OperationTable::opTable[operation];
}
