//
// Created by Mohammed Abdelbarry on 01-May-17.
//

#ifndef SIC_XE_ASSEMBLER_OPERATION_TABLE_H
#define SIC_XE_ASSEMBLER_OPERATION_TABLE_H


#include <string>
#include <map>
#include "instruction_info.h"

class operation_table {
public:
    static operation_table *getInstance();
    bool contains(std::string operation);
    instruction_info getInfo(std::string operation);

private:
    static operation_table *instance;
    std::map<std::string, instruction_info> opTable;
    operation_table();
    void initOpTable();
};


#endif //SIC_XE_ASSEMBLER_OPERATION_TABLE_H
