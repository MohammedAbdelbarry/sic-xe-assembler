//
// Created by salem.harby on 05/03/2017.
//

#include <functional>
#include <iostream>
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

    dirName = "START";
    info.label = Label::OPTIONAL;
    info.execute = [&](int &locCtr, Line) {
        //TODO: set locCtr to the specified starting address.
    };

    dirName = "BYTE";
    info.execute = [&](int &locCtr, Line) {
        locCtr++;
    };
    dirTable[dirName] = info;

    dirName = "WORD";
    info.execute = [&](int &locCtr, Line) {
        locCtr += 3;
    };
    dirTable[dirName] = info;

    dirName = "RESB";
    info.execute = [&](int &locCtr, Line) {
        //TODO: append locCtr by number of bytes specified.
    };
    dirTable[dirName] = info;

    dirName = "RESW";
    info.execute = [&](int &locCtr, Line) {
        //TODO: append locCtr by 3 * number of words specified.
    };
    dirTable[dirName] = info;

    dirName = "END";
    info.execute = [&](int &locCtr, Line) {
        //TODO: dk lol.
    };
    dirTable[dirName] = info;
}

bool DirectiveTable::contains(std::string directive) {
    return dirTable.find(directive) != dirTable.end();
}

DirectiveInfo DirectiveTable::getInfo(std::string directive) {
    return dirTable[directive];
}