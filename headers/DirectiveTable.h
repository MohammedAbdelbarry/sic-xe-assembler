/**
 * @file DirectiveTable.h
 * Directive table (holds all directives and their corresponding info).
 */

#ifndef SIC_XE_ASSEMBLER_DIRECTIVETABLE_H
#define SIC_XE_ASSEMBLER_DIRECTIVETABLE_H

#include "DirectiveInfo.h"
#include <map>
#include <string>

class DirectiveTable {
public:
    static DirectiveTable *getInstance();

    bool contains(std::string directive);

    DirectiveInfo getInfo(std::string directive);

private:
    static DirectiveTable *instance;
    std::map<std::string, DirectiveInfo> dirTable;

    DirectiveTable();

    void initDirTable();
};


#endif //SIC_XE_ASSEMBLER_DIRECTIVETABLE_H
