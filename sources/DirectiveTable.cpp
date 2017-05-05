//
// Created by salem.harby on 05/03/2017.
//

#include <functional>
#include <iostream>
#include <map>
#include <vector>
#include <regex>
#include "../headers/util.h"
#include "../headers/strutil.h"
#include "../headers/DirectiveInfo.h"
#include "../headers/DirectiveTable.h"

DirectiveTable *DirectiveTable::instance = nullptr;

DirectiveTable::DirectiveTable() {
    initDirTable();
}

DirectiveTable* DirectiveTable::getInstance() {
    if (instance == nullptr)
        instance = new DirectiveTable();
    return instance;
}

void DirectiveTable::initDirTable() {
    std::string dirName;
    DirectiveInfo info;
    const char HEX_BASE = 16;
    dirName = "START";
    info.label = Label::OPTIONAL;
    info.execute = [](int &locCtr, Line line) {
        try {
            //TODO: SET PROGRAM NAME = LABEL
            int pos = std::stoi(line.operand, 0, HEX_BASE);
            locCtr = pos;
        } catch(std::invalid_argument ex) {

        } catch(std::out_of_range ex) {

        }
        //TODO: set locCtr to the specified starting address.
    };
    dirTable[dirName] = info;

    dirName = "BYTE";
    info.execute = [](int &locCtr, Line line) {
        //TODO: check if the label is valid
        //TODO: check if the operand is a valid literal
        if (strutil::isCharLiteral(line.operand)) {
            int literalLength = line.operand.length() - 3;
            locCtr += literalLength;
        } else if (util::Hexadecimal::isHexLiteral(line.operand)){
            int literalLength = line.operand.length() - 3;
            locCtr += (literalLength / 2 + ((literalLength % 2) != 0));
        } else {
            locCtr += 1;
        }
    };
    dirTable[dirName] = info;

    dirName = "WORD";
    info.execute = [](int &locCtr, Line line) {
        //TODO: check if the label is valid
        //TODO: check if the operand is a valid literal
        if (strutil::isCharLiteral(line.operand)) {
            int literalLength = line.operand.length() - 3;
            locCtr += 3 * (literalLength / 3 + ((literalLength % 3) != 0));
        } else if (util::Hexadecimal::isHexLiteral(line.operand)){
            int literalLength = line.operand.length() - 3;
            locCtr += 3 * (literalLength / 6 + ((literalLength % 6) != 0));
        } else {
            locCtr += 3;
        }
    };
    dirTable[dirName] = info;

    dirName = "RESB";
    info.execute = [](int &locCtr, Line line) {
        try {
            int count = std::stoi(line.operand);
            locCtr += count;
        } catch(std::invalid_argument ex) {

        } catch(std::out_of_range ex) {

        }
        //TODO: append locCtr by number of bytes specified.
    };
    dirTable[dirName] = info;

    dirName = "RESW";
    info.execute = [](int &locCtr, Line line) {
        try {
            int count = std::stoi(line.operand);
            locCtr += count * 3;
        } catch(std::invalid_argument ex) {

        } catch(std::out_of_range ex) {

        }
        //TODO: append locCtr by 3 * number of words specified.
    };
    dirTable[dirName] = info;

    dirName = "END";
    info.execute = [](int &locCtr, Line) {
        //TODO: optional operand marks the start of the program.
    };
    dirTable[dirName] = info;
}

bool DirectiveTable::contains(std::string directive) {
    return dirTable.find(directive) != dirTable.end();
}

DirectiveInfo DirectiveTable::getInfo(std::string directive) {
    return dirTable[directive];
}