//
// Created by salem.harby on 05/03/2017.
//

#ifndef SIC_XE_ASSEMBLER_DIRECTIVETABLE_H
#define SIC_XE_ASSEMBLER_DIRECTIVETABLE_H


#include <string>
#include <map>
#include "DirectiveInfo.h"
#include <functional>

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
